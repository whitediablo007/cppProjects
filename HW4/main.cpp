
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

const double rectangleEqualsError = 0.01;

vector<RotatedRect>::iterator getIterator(vector<RotatedRect> &rectangles, const RotatedRect &rect);

vector<RotatedRect> &
getVector(double areaPrecision, const vector<vector<Point>> &contours, const vector<vector<Point>> &hulls,
          vector<RotatedRect> &rectangles);

int main() {
    const string path = "C:/Users/HOME/Desktop/HW4/Image.jpg";

    const double areaPrecision = 0.15;

    RNG rng(102938475600);

    Mat in = imread(path, IMREAD_COLOR);
    Mat grads;
    vector<Mat> results;

    vector<vector<Point>> contours;
    vector<vector<Point>> hulls;
    vector<RotatedRect> rectangles;

    std::vector<cv::Mat> channels;
    cv::split(in, channels);
    auto redChannel = channels[2];

    cv::imshow("Red", redChannel);
    cv::waitKey();

    Canny(redChannel, grads, 100, 150, 3);

    cv::imshow("Canny", grads);
    cv::waitKey();

    vector<Vec4i> hierarchy;
    findContours(grads, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    hulls.resize(contours.size());

    for (int i = 0; i < contours.size(); ++i)
        convexHull(contours[i], hulls[i]);

    rectangles = getVector(areaPrecision, contours, hulls, rectangles);

    Mat result(in.clone());
    for (auto &rectangle: rectangles) {
        auto color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        Point2f rectPoints[4];
        rectangle.points(rectPoints);
        for (int j = 0; j < 4; ++j) {
            line(result, rectPoints[j], rectPoints[(j + 1) % 4], color, 3);
        }
    }
    imshow("Result image", result);

    for (const auto &rotatedRect: rectangles) {
        try {
            results.push_back(in(rotatedRect.boundingRect()).clone());
        }
        catch (...) {

        }
    }

    for (int i = 0; i < results.size(); ++i) {
        string winName = "Image " + to_string(i);
        namedWindow(winName, WINDOW_KEEPRATIO);
        resizeWindow(winName, results[i].size() * 2);
        imshow(winName, results[i]);
    }

    waitKey();
}

vector<RotatedRect> &
getVector(const double areaPrecision, const vector<vector<Point>> &contours, const vector<vector<Point>> &hulls,
          vector<RotatedRect> &rectangles) {
    for (int i = 0; i < contours.size(); ++i) {

        double contour_Area = contourArea(contours[i]);
        double hull_Area = contourArea(hulls[i]);

        if (hull_Area < 2000 || hull_Area > 15000)
            continue;

        if (contour_Area / hull_Area - 1 > areaPrecision)
            continue;


        RotatedRect rect = minAreaRect(hulls[i]);

        auto iter = getIterator(rectangles, rect);

//        if (hierarchy[i][2] == -1)
//           continue;

        if (iter != rectangles.end())
            continue;

        rectangles.push_back(rect);
    }
    return rectangles;
}

vector<RotatedRect>::iterator getIterator(vector<RotatedRect> &rectangles, const RotatedRect &rect) {
    vector<RotatedRect>::iterator iter;
    iter = find_if(rectangles.begin(), rectangles.end(),
                   [&rect](auto rectangle) {
                       auto rect1 = rect.boundingRect();
                       auto rect2 = rectangle.boundingRect();
                       return abs(rect1.x - rect2.x) < max(rect1.x, rect2.x) * rectangleEqualsError &&
                              abs(rect1.y - rect2.y) < max(rect1.y, rect2.y) * rectangleEqualsError;
                   }
    );
    return iter;
}
