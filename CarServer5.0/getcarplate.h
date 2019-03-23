#ifndef GETCARPLATE_H
#define GETCARPLATE_H
#include "plate.h"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/features2d.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include "time.h"
#include  <QObject>
using namespace std;
using namespace cv;
class GetCarPlate
{
public:

    GetCarPlate();
    vector<Plate> Contour(cv::Mat &img);
    bool verifySizes(cv::RotatedRect mr);
    cv::Mat histeq(cv::Mat in);
    bool showSteps;
    bool saveRecognition;
    string filename;
};

#endif // GETCARPLATE_H
