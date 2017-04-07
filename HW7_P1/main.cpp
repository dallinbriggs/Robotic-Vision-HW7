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
    Mat image_video;
    int channels;
    //    Mat corners;
    Size patternsize;
    string filename;
    string header;
    string tail;
    vector<Point> pyramid;
    Size winsize = Size(21,21);
    vector<Point2f> corners, corners_prev,corners_next;
    vector<uchar> status;
    vector<float> err;
    vector<float> y, y_prime, x, x_prime, ax, ay;
    vector<vector<float>> y_mat, y_prime_mat;
    Mat a;
    vector<float> a_vec;
    float tau;
    Mat tau_matrix(19,2,CV_32F);



    //    VideoWriter Vout;
    //    Vout.open("VideoOut.avi",CV_FOURCC('M', 'P', 'E', 'G') , 1, Size(640,480),1);

    header = "/home/dallin/robotic_vision/HW7/Time_To_Impact_Images/T";
    tail = ".jpg";

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
        //        goodFeaturesToTrack(image_prev,corners_prev,500,.01,5,noArray(),3,false,.04);



        corners_prev = corners;
        if(corners.empty())
        {
            Mat mask(image.size(),CV_8U,Scalar(0));
            rectangle(mask,Point(271,160),Point(373,364),Scalar(255),CV_FILLED,LINE_8,0);
            goodFeaturesToTrack(image,corners,500,.01,10,mask,3,false,.04);

        }

        //        buildOpticalFlowPyramid(corners, pyramid, winsize,500,false,BORDER_REFLECT_101,BORDER_CONSTANT,true);
        if(corners_prev.empty())
        {
            cout<< "No corners!" << endl;
        }
        else
        {
            calcOpticalFlowPyrLK(image_prev,image,corners_prev,corners,status,err,winsize,3,
                                 TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,.01),0,1e-4);
        }
        for(int i=0; i<corners_prev.size(); i++)
        {
            circle(image_color,corners_prev[i],2,Scalar(0,255,0),2,LINE_8,0);
        }
        for(int i=0; i<corners_prev.size(); i++)
        {
            line(image_color,corners[i],corners_prev[i],Scalar(0,0,255),2,LINE_8,0);
        }


        Mat coord_prime(2*corners.size(),1, CV_32F);
        for(int i=0; i<corners.size(); i++)
        {
            coord_prime.at<float>(2*i,0) = corners[i].x-320;
            coord_prime.at<float>(2*i+1,0) = corners[i].y-240;
        }


        Mat coord(2*corners_prev.size(),1, CV_32F);
        for(int i=0; i<corners_prev.size(); i++)
        {
            coord.at<float>(2*i,0) = corners_prev[i].x-320;
            coord.at<float>(2*i+1,0) = corners_prev[i].y-240;
        }

        if(!corners_prev.empty())
        {
            Mat coord_inv(1,2*corners_prev.size(), CV_32F);
            invert(coord,coord_inv, DECOMP_SVD);
            a = coord_inv*coord_prime;
            tau = a.at<float>(0,0)/(a.at<float>(0,0)-1);
            tau_matrix.at<float>(i,0) = i;
            tau_matrix.at<float>(i,1) = tau;

        }


        imshow("Image Color", image_color);
        waitKey(5);

    }

    cout << tau_matrix << endl;


    waitKey(0);

    return 0;
}
