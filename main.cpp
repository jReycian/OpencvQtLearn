#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

Mat img;
vector<vector<int>> newPoint;

vector<vector<int>> myColor {{154,94,147,179,255,255}, //blue
                             {91,57,76,116,255,255}}; // red
vector<Scalar> myColorValues {{0, 0, 255}, // blue
                              {255, 0, 0}}; // red

void callImage()
{
    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\test.bmp";
    img = imread(path);
    Mat img2;

    resize(img, img2, Size(), 0.5, 0.5);
    imshow("Image", img);
    imshow("Resize Image", img2);
    waitKey(0);
}

void callVideoFile()
{

    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\Robot.MP4";
    VideoCapture cap(path);
    Mat img2;

    while (true)
    {
        cap.read(img);
        resize(img, img2, Size(), 0.2, 0.2);
        imshow("Image", img2);
        waitKey(20);
    }

}

void callCamera()
{

    VideoCapture cap(0), cap2(1);
    Mat frame, frame2;

    while (true)
    {
        cap.read(frame);
        cap2.read(frame2);
        imshow("Camera 1", frame);
        imshow("Camera 2", frame2);
        waitKey(1);
    }
}

void callImagePreprocess()
{
    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\leo.jpg";
    img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    erode(imgCanny, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgErode);

    waitKey(0);
}

void imageResize() // Resize and Crop
{
    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\leo.jpg";
    img = imread(path);
    Mat imgResize, imgCrop;

    cout << img.size << endl;
    resize(img, imgResize, Size(), 0.5, 0.5);

    Rect roi(380, 20, 290, 250);
    imgCrop = img(roi);

    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);

    waitKey(0);
}

void drawShapes()
{
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

    circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "Disect Coder", Point(150, 265), FONT_HERSHEY_PLAIN, 2, Scalar(0, 69, 255), 2);

    imshow("Image", img);
    waitKey(0);
}

float w = 250, h = 350;
Mat matrix, imgWarp;

void warpPerspective()
{
    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\cards.jpg";
    img = imread(path);

    Point2f src[4] = {{40, 214}, {227, 183}, {57, 424}, {271, 382}};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++)
    {
        // print point position on the selectd card
        circle(img, src[i], 5, Scalar(0, 0, 255), FILLED);
    }

    imshow("Image", img);
    imshow("Image Warp", imgWarp);
    waitKey(0);
}

void colorDetection()
{
    int hmin = 0, smin =  0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\color.jpg";
    img = imread(path);
    Mat imgHSV, mask;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    namedWindow("Trackbars");

    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);

    createTrackbar("Saturation Min", "Trackbars", &smin, 255);
    createTrackbar("Saturation Max", "Trackbars", &smax, 255);

    createTrackbar("Value Min", "Trackbars", &vmin, 255);
    createTrackbar("Value Max", "Trackbars", &vmax, 255);

    while (true) {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", img);
        imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);
        waitKey(1);
    }

}

void getContour(Mat imgDil, Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //    drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        string objectType;

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.01 * peri, true);

            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);

            int shape = (int) conPoly[i].size();

            if (shape == 3)
                objectType = "Triangle";
            else if (shape == 4)
            {
                float aspRatio = (float) boundRect[i].width / (float) boundRect[i].height;
                cout << aspRatio << endl;
                if (aspRatio > 0.98 && aspRatio < 1.05)
                {
                    objectType = "Square";
                }
                else
                {
                    objectType = "Rectangle";
                }
            }
            else if (shape == 5)
                objectType = "Pentagon";
            else if (shape == 6)
                objectType = "Hexagon";
            else if (shape > 6)
                objectType = "Circle";

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
            putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);

        }
    }
}

void ShapeDetection()
{
    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\color.jpg";
    img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil;

    // Preprocessing
    cvtColor(img, imgGray, COLOR_BGRA2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    getContour(imgDil, img);

    imshow("Image", img);
    //    imshow("Image Gray", imgGray);
    //    imshow("Image Blur", imgBlur);
    //    imshow("Image Canny", imgCanny);
    //    imshow("Image Dilate", imgDil);
    waitKey(0);
}

Point getPainterContour(Mat imgDil)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //    drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    Point myPoint(0,0);

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.01 * peri, true);

            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
        }
    }
    return myPoint;
}

vector<vector<int>> findColor(Mat img)
{
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for (int i = 0; i < myColor.size(); i++)
    {
        Scalar lower(myColor[i][0], myColor[i][1], myColor[i][2]);
        Scalar upper(myColor[i][3], myColor[i][4], myColor[i][5]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        string name = to_string(i);
        if (name == "0")
        {
            name  = "blue";
        }
        else if (name == "1")
        {
            name = "red";
        }
        //        imshow(name, mask);
        Point myPoint = getPainterContour(mask);
        if (myPoint.x != 0 && myPoint.y != 0)
        {
            newPoint.push_back({myPoint.x, myPoint.y, i});
        }
    }
    return newPoint;
}

void drawOnCanvas(vector<vector<int>> newPoint, vector<Scalar> myColorValues)
{
    for (int i = 0; i < newPoint.size(); i++)
    {
        circle(img, Point(newPoint[i][0], newPoint[i][1]), 10, myColorValues[newPoint[i][2]], FILLED);
    }
}

void virtualPainter()
{
    VideoCapture cap(0);

    while (true)
    {
        cap.read(img);
        newPoint = findColor(img);
        drawOnCanvas(newPoint, myColorValues);

        imshow("Camera", img);
        waitKey(1);
    }
}

int main (){

    //    callImage();
    //    callVideoFile();
    //    callCamera();
    //    callImagePreprocess();
    //    imageResize();
    //    drawShapes();
    //    warpPerspective();
    //    colorDetection();
    //    ShapeDetection();
    virtualPainter();

    return 0;
}
