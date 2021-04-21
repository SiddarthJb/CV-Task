#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;

class FaceDetection {
    cv::CascadeClassifier _cascade;
    cv::VideoCapture _capture;

    public:
        FaceDetection(){
            _capture.open(0);   
        }

        int setCascade (std::string cascadePath);
        cv::Mat getFrame();
        std::vector<cv::Rect> detectAndDisplay();
};

int main( int argc, const char** argv )
{
    FaceDetection detect;
    detect.setCascade("/home/siddarth/opencv/install/haarcascade_frontalface_alt.xml");
    cv::Mat overlay = cv::imread("/home/siddarth/opencv/install/image.jpeg");
    while (true)
    {
        cv::Mat frame = detect.getFrame();
        std::vector<cv::Rect> faces = detect.detectAndDisplay();
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            cv::Point pt1(faces[i].x ,faces[i].y);
            cv::Point pt2(faces[i].x + faces[i].width,faces[i].y + faces[i].height);
            cv::rectangle(frame,pt1,pt2,(255,0,255),2);

            cv::Rect Roi(faces[i].x ,faces[i].y,faces[i].height, faces[i].width);
            cv::resize(overlay, overlay, cv::Size(faces[i].height, faces[i].width));
            overlay.copyTo( frame(Roi) );
        }
        cv::imshow( "Capture - Face detection", frame );
        if( cv::waitKey(10) == 27 )
        {
            break;
        }
    }
    return 0;
}

    int FaceDetection::setCascade (std::string cascadePath){
        if( !_cascade.load(cascadePath) ){
            cout << "--(!)Error loading face cascade\n";
            return -1;
            }
    }
    
    cv::Mat FaceDetection::getFrame(){
        cv::Mat _frame;
        if (_capture.isOpened()){
            _capture.read(_frame);
            return _frame;
        }
    }

    std::vector<cv::Rect> FaceDetection::detectAndDisplay(){
        cv::Mat _frame = getFrame();
        cv::Mat frame_gray;
        cv::cvtColor( _frame, frame_gray, cv::COLOR_BGR2GRAY );
        cv::equalizeHist( frame_gray, frame_gray );

        std::vector<cv::Rect> faces;
        _cascade.detectMultiScale( frame_gray, faces );
        return faces;
    } 