#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <ctime>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;
void getContours(Mat imgDil, Mat img) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
   // drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);

        if (area > 1000) {
           //  float param = arcLength()

            drawContours(img, contours, i, Scalar(255, 0, 255), 2);
        }
    }
}

int main(int argc, char* argv[]) {
    VideoCapture cap(0);//captRefrnc(sourceReference);//, captUndTst(sourceCompa                                                                                        reWith);
    Mat img;
   // Mat img_grey;
    //Mat img_blur;
    //Mat img_canny;
   // Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    CascadeClassifier face_cascade;
    face_cascade.load("D:/Antony/Programing_C++/EVM/Resources/haarcascade_frontalface_default.xml");
    if (face_cascade.empty()) { cout << "bad xml"; }
   // int frame_count;
    clock_t start = clock();
    long frame_count = 0;
    clock_t get_time;
    clock_t get_time_end;
    clock_t get_full_time;
    clock_t get_full_time_end;
    double web = 0;
    double proc = 0;
    double th_3 = 0;
    double th_4 = 0;
    double full_time;
    get_full_time = clock();
    while (true) {
        get_time = clock();
        cap.read(img);
        get_time_end = clock();
        web += get_time_end - get_time;
        frame_count++;
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        putText(img, "FPS:" + to_string(frame_count / seconds), Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255) , 1);
        //frame_count++;
       // cvtColor(img, img_grey, COLOR_BGR2GRAY);
       // GaussianBlur(img, img_blur,Size(7,7),10,2);
       // Canny(img, img_canny, 50, 50);
       // cout << img.size<<" ";    
       // imshow("Image", img);
       /// imshow("Image Blur", img_blur);
        //imshow("Image Gray", img_grey);
       // imshow("Image Canny", img_canny);
        //circle(img, Point(300, 256), 155, Scalar(0, 69, 255), FILLED);
        //rectangle(img, Point(175, 230), Point(420,280), Scalar(255, 255, 255), FILLED);
      
        // Preprocessing
        //cvtColor(img, imgGray, COLOR_BGR2GRAY);
        //GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
        //Canny(imgBlur, imgCanny, 25, 75);
        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        //dilate(imgCanny, imgDil, kernel);

        //getContours(imgDil, img);

       

       // Mat matrix, imgWarp,img_HSV;
        //float w = 350, h = 550;

     /*   Point2f src[4] = { {200,242},{240,300},{350,242},{350,310} };
        Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

        matrix = getPerspectiveTransform(src, dst);
        warpPerspective(img, imgWarp, matrix, Point(w, h));

        for (int i = 0; i < 4; i++)
        {
            circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
        }*/
       // cvtColor(img, img_HSV, COLOR_BGR2HSV);
        //imshow("Image HSV", img_HSV);

       
        vector<Rect> faces;
        get_time = clock();
        face_cascade.detectMultiScale(img, faces, 1.1, 10);
        get_time_end = clock();
        proc += get_time_end - get_time;

        for (int i = 0; i < faces.size(); i++) {
            rectangle(img,faces[i].tl(),faces[i].br(), Scalar(255, 0, 0), 2);
        }
       
        string str = "Detected " + to_string(faces.size()) + " fases";
        putText(img, str, Point(300, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 1);

        imshow("Image", img);
        char c = waitKey(5);
        if (c == 27) break;
    }
    return 0;
}
