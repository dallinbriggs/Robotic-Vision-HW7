%% Task 1

clear
clf;
close all;

data = [ 2, 42.908047;
    3, 45.469345;
    4, 39.176193;
    5, 46.069511;
    6, 37.279297;
    7, 39.932579;
    8, 36.148632;
    9, 38.43544;
    10, 32.85878;
    11, 35.219383;
    12, 32.762516;
    13, 34.040325;
    14, 29.913671;
    15, 30.404102;
    16, 28.948425;
    17, 28.946936;
    18, 25.68087];

x = data(:,1);
y = data(:,2)';

A = [x, ones(length(x),1)];

% c = inv(A'*A)*A'*y';
c = A\y';
x_fine = 0:.1:42;
yr = c(1)*x_fine+c(2);

hold on;
scatter(x,y,'filled');
plot(x_fine,yr);
xlabel('Frame');
ylabel('Estimated Distance (# of Frames)');
hold off;

%% Task 2
clear
clf
close all

data = [ 2, 42.908047;
    3, 45.469345;
    4, 39.176193;
    5, 46.069511;
    6, 37.279297;
    7, 39.932579;
    8, 36.148632;
    9, 38.43544;
    10, 32.85878;
    11, 35.219383;
    12, 32.762516;
    13, 34.040325;
    14, 29.913671;
    15, 30.404102;
    16, 28.948425;
    17, 28.946936;
    18, 25.68087];

x = data(:,1);
y = data(:,2)'*15.25;

A = [x, ones(length(x),1)];

% c = inv(A'*A)*A'*y';
c = A\y';
x_fine = 0:.1:42;
yr = c(1)*x_fine+c(2);

hold on;
scatter(x,y,'filled');
plot(x_fine,yr);
xlabel('Frame');
ylabel('Estimated Distance (mm)');
hold off;


%% Task 3
clear
clf
close all

data = [1, 608.50385;
    2, 593.85883;
    3, 580.33142;
    4, 564.14392;
    5, 551.20764;
    6, 535.31183;
    7, 521.34967;
    8, 506.39935;
    9, 493.34311;
    10, 478.5777;
    11, 463.84497;
    12, 449.69211;
    13, 436.22684;
    14, 420.44684;
    15, 405.31024;
    16, 389.82211;
    17, 375.04077;
    18, 358.51971];

x = data(:,1);
y = data(:,2)';

A = [x, ones(length(x),1)];

% c = inv(A'*A)*A'*y';
c = A\y';
x_fine = 0:.1:42.5;
yr = c(1)*x_fine+c(2);

hold on;
scatter(x,y,'filled');
plot(x_fine,yr);
xlabel('Frame');
ylabel('Estimated Distance (mm)');
hold off;






