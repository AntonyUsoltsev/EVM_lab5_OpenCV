#include <iostream> 
#include <string>   
#include <ctime>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>


// questions : 
// падает фпс при черной картинке и растет при белой
// при статитчной (или не черной) картинке camera_time значительно меньше 
// что участвует в обработке/считываниие картинки
// как правильно считать фпс все кадры на все секунды или считать секунду и смотреть сколько кадров было 

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    VideoCapture cap(0);                                               
    Mat img;

    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_default.xml");
    if (face_cascade.empty()) { cout << "bad xml"; }
    
    long frame_count = 0;
    clock_t read_time, read_time_end, face_time, face_time_end;
    clock_t draw_time, draw_time_end, output_time, output_time_end;
    clock_t full_time, full_time_end;
    double all = 0, camera = 0, face_proc = 0, draw = 0,output = 0;

    full_time = clock();
    clock_t start = clock();
    while (true) {

        read_time = clock();
        cap.read(img);
        read_time_end = clock();
        camera += (read_time_end - read_time);

        frame_count++;
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;

        vector<Rect> faces;

        face_time = clock();
        face_cascade.detectMultiScale(img, faces, 1.1, 10);
        face_time_end = clock();
        face_proc += (face_time_end - face_time);

        draw_time = clock();

        putText(img, "FPS:" + to_string(frame_count / seconds), Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 1);
        for (int i = 0; i < faces.size(); i++) 
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 2);
        string str = "Detected " + to_string(faces.size()) + " faces";
        putText(img, str, Point(300, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 1);

        draw_time_end = clock();
        draw += (draw_time_end - draw_time);

        output_time = clock();
        imshow("Image", img);
        output_time_end = clock();
        output += (output_time_end - output_time);

        char c = waitKey(5);
        
        if (c == 27) break;
    }

    full_time_end = clock();
    all = full_time_end - full_time;
    cout << "All time: " << all << endl;
    cout << "Camera time: " << camera<<" -> " << camera / all * 100 << "%" << endl;
    cout << "Face_proc time: " << face_proc << " -> " << face_proc / all * 100 << "%" << endl;
    cout << "Draw time: " << draw << " -> " << draw / all * 100 << "%" << endl;
    cout << "Output time: " << output << " -> " << output / all * 100 << "%" << endl;
    return 0;
}
