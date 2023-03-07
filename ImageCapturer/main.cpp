#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main ()
{
    VideoCapture cap(0);
    Mat img, img2;
    int name = 0;

    string path = "C:\\Users\\MinebeaMitsumi\\Desktop\\OpenCVLearn\\OpenCVCourseQT\\Resources\\Camera""";
    string fileType = ".jpg";

    if (!cap.isOpened())
    {
        cout << "Cannot open Camera";
    }
    while (cap.isOpened())
    {
        cap.read(img);

        imshow("Camera", img);

        if (waitKey(10) == 's')
        {
            img2 = img.clone();
            imshow("Capture", img2);
            imwrite(path, img2);

        }

        if (waitKey(10) == 'space')
            break;
    }
    cap.release();
}
