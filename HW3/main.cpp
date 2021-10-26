#include <iostream>
#include <Eigen/Core>

#include <cmath>
#include <vector>

using namespace std;
using namespace Eigen;

float a = 1.2;
float b = 1.3;
float d = 0.5;
double maxDif = 0;

//функция, которую будем интегрировать
double myFunction(double t, double u) {
    return (a * t - b * u);
}

//аналитическое решение
double analyticalFunc(double t) {
    double c = d + (a / (pow(b, 2)));
    double answer = (a / b) * (t - (1 / b)) + c * exp(-b * t);
    return answer;
}

//метод Рунге-Кутты 4 порядка
double runge4(double t, double y0, double step) {
    //Рассчитываем коэффициенты
    double k1, k2, k3, k4;
    k1 = myFunction(t, y0);
    k2 = myFunction(t + step / 2, y0 + step * k1 / 2);
    k3 = myFunction(t + step / 2, y0 + step * k2 / 2);
    k4 = myFunction(t + step, y0 + step * k3);
    double y = y0 + (k1 + 2 * k2 + 2 * k3 + k4) * step / 6;
    return y;
}

int main(int argc, char *argv[]) {
    cout << "HW 3" << endl;
    double initVal = d;
    double step = 0.01;
    //вектора отсчета времени и значений Y
    vector<double> time, y;
    //начальное значение времени
    time.push_back(0);
    //начальное значение Y
    y.push_back(initVal);

    for (double t = step; t < 1 + step / 2; t += step) {
        //back возвращает последний элемент
        double dy = runge4(time.back(), y.back(), step);
        //push_back аналогична append
        time.push_back(t);

        y.push_back(dy);
    }
    for (int i = 0; i < time.size(); i++) {
        cout << "u(t) = " << analyticalFunc(time[i]) << " y(t)= " << y[i] << endl;
        if (maxDif <= abs(analyticalFunc(time[i]) - y[i])) {
            maxDif = abs(analyticalFunc(time[i]) - y[i]);
        }

    }
    cout << endl;
    cout << "Max |u(t) - y(t)| = " << maxDif << endl;
    return 0;
}
