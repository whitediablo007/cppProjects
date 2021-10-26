#include <iostream>
#include <Eigen/Core>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main(int argc, char *argv[]) {
    // для рассогласований
    double maxD, minMaxD;
    // для номеров измерений
    int randNum1, randNum2;
    //матрица коэффциентов
    Matrix2d matT;
    //вектор правых частей
    Vector2d vecB;
    //вектор ответов - А и В
    Vector2d solution, solutionMin;

    //вектора без выбросов
    VectorXd vecZ(9),
            vecT(9),
            vecU(9),
            vecDif(9);//вектора Z, T, U = Ln(Z), dif - рассогласование
    //вектор Z
    vecZ << 27, 31, 43, 58, 69, 86, 102, 111, 122;
    //вектор T
    vecT << 71, 64, 52, 41, 33, 23, 17, 12, 2;

    cout << "----------Vectors---------" << endl;
    for (int i = 0; i < 9; i++) {
        //прологарифмировали
        vecU[i] = log(vecZ[i]);
    }
    cout << "vecZ:   vecT:   vecU:" << endl;
    for (int i = 0; i < 9; i++) {
        cout << vecZ(i) << "      " << vecT(i) << "      " << vecU(i) << endl;
    }
    //начальное значение
    minMaxD = 100;
    //количество итераций
    for (int i = 0; i < 100; i++) {
        cout << "\n ----------Finding A and B---------" << endl;
        //задаем две случайные точки
        randNum1 = rand() % 9;
        randNum2 = rand() % 9;
        //чтобы числа не были одинаковыми
        while (randNum2 == randNum1) {
            randNum2 = rand() % 9;
        }
        //устанавливаем значения температуры
        matT << vecT[randNum1], 1, vecT[randNum2], 1;
        // значения u = (ln(z))
        vecB << vecU[randNum1], vecU[randNum2];
        //получаем А и В
        solution = matT.colPivHouseholderQr().solve(vecB);

        cout << "\n solution: \n" << solution << endl;
        cout << "\n ----------Recounting----------" << endl;
        //инициализируем нулем
        maxD = 0;
        //проходим по всем парам, подставляем А и В
        for (int i = 0; i < 9; i++) {
            //пересчитываем из логарифма
            double y = exp(solution(0) * vecT(i) + solution(1));
            //рассогласование
            vecDif(i) = abs(y - vecZ(i));
            //находим самое большое рассогласование
            if (maxD < vecDif(i)) {
                maxD = vecDif(i);
            }
        }
        cout << "Maximum diff [" << i << "] = " << maxD << endl;

        cout << "----------Searching minimum of max try [" << i + 1 << "] of 100 ---------" << endl;
        cout << "\n minMaxD = " << minMaxD << " and actual maxD = " << maxD << endl;
        if (minMaxD > maxD) {
            minMaxD = maxD;
            solutionMin = solution;
        }
        cout << "\n new minMaxD = " << minMaxD << endl;

    }
    cout << "----------Final---------" << endl;
    cout << "\n Best result:"
            "\n A = " << solutionMin(0) <<
         "\n B = " << solutionMin(1) <<
         "\n Z = " << exp(solutionMin(1)) << " * exp(" << solutionMin(0) << "*T)" << endl;

    return 0;
}
