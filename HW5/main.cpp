#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src, src2, imageWithKeyPoints, imageWithKeyPoints2;
    Mat desc1, desc2, img_matches;

    vector<KeyPoint> keys1, keys2;
    vector<DMatch> matches;

    Ptr<FeatureDetector> detector;
    Ptr<DescriptorExtractor> extractor;
    BFMatcher matcher;

    //открываем видео
    VideoCapture cap("F:/magistratura/11-21/STZ/sample_mpg.avi");

    // проверяем, открывается, или нет
    if (!cap.isOpened()) {
        return -1;
    }
    bool stop = false;

    double rate = cap.get(CAP_PROP_FPS);

    int delay = 100 / rate;
    cout << "Frame rate of video is " << rate << endl;

    //детектор и экстрактор SURF
//    detector = xfeatures2d::SURF::create();
//    extractor = xfeatures2d::SURF::create();

//    detector = SIFT::create();
//    extractor = SIFT::create();

    //детектор и экстрактор BRISK
    detector = BRISK::create();
    extractor = BRISK::create();

    cap.grab();
    cap >> src2;

    detector->detect(src2, keys2);              //находим точки на первом кадре
    extractor->compute(src2, keys2, desc2);    //строим их описание

    while (!stop) {
        //Проверяем доступность кадра
        bool result = cap.grab();
        //считываем
        if (result)
            cap >> src;
        else
            continue;

        detector->detect(src, keys1);                   //находим точки на кадре
        extractor->compute(src, keys1, desc1);         //описание точек

        matcher.match(desc1, desc2, matches);     //совпадения
        drawMatches(src, keys1, src2, keys2, matches, img_matches);  //отрисовка
        imshow("matches", img_matches);

        src2 = src;    //обработанный кадр
        detector->detect(src2, keys2);              //точки на первом кадре
        extractor->compute(src2, keys2, desc2);    //описание точек

        int key = waitKey(delay);
        if (key == 27)
            stop = true;
    }

}
