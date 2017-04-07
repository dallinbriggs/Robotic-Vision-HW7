#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat image;
    Mat image_color;
    Mat image_prev;
    string filename;
    string header;
    string tail;
    Size winsize = Size(21,21);
    vector<Point2f> corners, corners_prev;
    vector<uchar> status;
    vector<float> err;
    Mat data(19,2,CV_32F);

    float Z, X;

    header = "/home/dallin/robotic_vision/HW7/Time_To_Impact_Images/T";
    tail = ".jpg";

    Mat M = (Mat_<double>(3,3) <<  825.0900600547, 0, 331.6538103208,
             0, 824.2672147458,  252.9284287373,
             0, 0, 1);
    Mat d = (Mat_<double>(5,1) << -0.2380769337,
             0.0931325835,
             0.0003242537,
             -0.0021901930,
             0.4641735616);

    // Width of the Can is 59 mm. This will be used to calc the distance to the can.

    for (int i = 1; i < 19; i+=1)
    {
        filename = header + to_string(i) + tail;
        if(image.empty())
        {
            image = Mat::zeros(480,640,CV_32F);
        }

        image_prev = image.clone();
        image = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
        image_color = imread(filename,CV_LOAD_IMAGE_COLOR);

        corners_prev = corners;
        if(corners.empty())
        {
            Mat mask(image.size(),CV_8U,Scalar(0));
            rectangle(mask,Point(284,160),Point(365,364),Scalar(255),CV_FILLED,LINE_8,0);
            goodFeaturesToTrack(image,corners,500,.01,10,mask,3,false,.04);
        }

        if(corners_prev.empty())
        {
            cout<< "No corners!" << endl;
        }
        else
        {
            calcOpticalFlowPyrLK(image_prev,image,corners_prev,corners,status,err,winsize,3,
                                 TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,.01),0,1e-4);
        }
        for(int i=0; i<corners.size(); i++)
        {
            circle(image_color,corners[i],2,Scalar(0,255,0),2,LINE_8,0);
        }

        float x_small = 640;
        float x_large = 0;
        int x_small_index, x_large_index;
        for(int i = 0; i<corners.size(); i++)
        {
            if(corners[i].x < x_small)
            {
                x_small = corners[i].x;
                x_small_index = i;
            }
            if(corners[i].x > x_large)
            {
                x_large = corners[i].x;
                x_large_index = i;
            }
        }

        Z = 825.09*59.0/(x_large - x_small);
        data.at<float>(i,0) = i;
        data.at<float>(i,1) = Z;

        imshow("Image Color", image_color);
        waitKey(1);

    }


    cout << data << endl;
    waitKey(0);

    return 0;
}
