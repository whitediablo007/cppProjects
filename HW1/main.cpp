#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
const int size = 4;

float maxElement, temp;
int maxRow, maxCol;

int ch1 = 0;
int ch2 = 0; //для запоминания элементов
bool answ = true;

void setupArr(int length, float array[]);

void setupArrOnes(int length, float array[]);

void setupOnesOnMainDiagonal(int length, float array[][size]);

void setupOnSecondaryDiagonal(int length, float array[][size]);

void setupOnMainDiagonal(int length, float array[][size]);

void copyMatrix(float array1[][size], float array2[][size]);

void printMatrix(float array1[], float array2[][size]);

void changeLines(float array1[], float array2[][size]);

void upperTriangle(float array1[], float array2[][size]);

void printMatrix(float array1[][size], float array2[][size]);

int main() {

    cout << setprecision(3);
    cout << "Task 1" << endl;

    float arrA[size][size],
            arrCopy[size][size],
            arrB[size],
            arrX[size],
            arrOnes[size][size];

    while (true) {
        int n;

        cout << endl;
        cout << "Enter sample number: " << endl;

        cout << "Chose matrix:"
                "\n [1] - 1 on the main line;"
                "\n [2] - Numbers 1-4 on the main line; "
                "\n [3] - Numbers 1-4 on the sub-line"
                "\n [4] - Zero on the main line"
                "\n [5] - Wrong matrix"
                "\n [6] - Simple matrix"
                "\n [7] - Task matrix"
                "\n [8] - EXIT" << endl;

        cin >> n;

        switch (n) {
            case 1:
                setupOnesOnMainDiagonal(size, arrA);
                setupArr(size, arrB);
                break;

            case 2:
                setupOnMainDiagonal(size, arrA);
                setupArr(size, arrB);
                break;

            case 3:
                setupOnSecondaryDiagonal(size, arrA);
                setupArrOnes(size, arrB);
                break;
            case 4:
                arrA[0][0] = 1;
                arrA[0][1] = 2;
                arrA[0][2] = 0;
                arrA[0][3] = 0;
                arrA[1][0] = 2;
                arrA[1][1] = 4;
                arrA[1][2] = 3;
                arrA[1][3] = 0;
                arrA[2][0] = 0;
                arrA[2][1] = 2;
                arrA[2][2] = 0;
                arrA[2][3] = 0;
                arrA[3][0] = 0;
                arrA[3][1] = 0;
                arrA[3][2] = 0;
                arrA[3][3] = 4;

                setupArrOnes(size, arrB);
                break;
            case 5:
                arrA[0][0] = 1;
                arrA[0][1] = 2;
                arrA[0][2] = 3;
                arrA[0][3] = 4;
                arrA[1][0] = 5;
                arrA[1][1] = 6;
                arrA[1][2] = 7;
                arrA[1][3] = 8;
                arrA[2][0] = 9;
                arrA[2][1] = 10;
                arrA[2][2] = 11;
                arrA[2][3] = 12;
                arrA[3][0] = 16;
                arrA[3][1] = 15;
                arrA[3][2] = 14;
                arrA[3][3] = 13;

                setupArrOnes(size, arrB);
                break;
            case 6:
                arrA[0][0] = 1;
                arrA[0][1] = 2;
                arrA[0][2] = 3;
                arrA[0][3] = 4;
                arrA[1][0] = -1;
                arrA[1][1] = -2;
                arrA[1][2] = 0;
                arrA[1][3] = 3;
                arrA[2][0] = 0;
                arrA[2][1] = 6;
                arrA[2][2] = 11;
                arrA[2][3] = 2;
                arrA[3][0] = 4;
                arrA[3][1] = -2;
                arrA[3][2] = 1;
                arrA[3][3] = 0;

                arrB[0] = 5;
                arrB[1] = -2;
                arrB[2] = 14;
                arrB[3] = 4;
                break;
            case 7:
                arrA[0][0] = 10;
                arrA[0][1] = 6;
                arrA[0][2] = 2;
                arrA[0][3] = 0;
                arrA[1][0] = 5;
                arrA[1][1] = 1;
                arrA[1][2] = -2;
                arrA[1][3] = 4;
                arrA[2][0] = 3;
                arrA[2][1] = 5;
                arrA[2][2] = 1;
                arrA[2][3] = -1;
                arrA[3][0] = 0;
                arrA[3][1] = 6;
                arrA[3][2] = -2;
                arrA[3][3] = 2;

                arrB[0] = 25;
                arrB[1] = 14;
                arrB[2] = 10;
                arrB[3] = 8;
                break;
            case 8:
                return 0;
        }
        //копирование матрицы
        copyMatrix(arrCopy, arrA);

        //вывод в консоль начальной матрицы
        cout << "Original matrix" << endl;
        printMatrix(arrB, arrA);

        //выбор главного элемента по строкам
        cout << "Changing lines" << endl;
        changeLines(arrB, arrA);
        //вывод в консоль
        printMatrix(arrB, arrA);

        //получение верхнетреугольной матрицы
        cout << "Upper triangle" << endl;
        upperTriangle(arrB, arrA);
        //вывод в консоль
        printMatrix(arrB, arrA);

        //нахождение решения
        cout << "solution" << endl;
        arrX[3] = arrB[3] / arrA[3][3];
        arrX[2] = (arrB[2] - arrX[3] * arrA[2][3]) / arrA[2][2];
        arrX[1] = (arrB[1] - arrX[2] * arrA[1][2] - arrX[3] * arrA[1][3]) / arrA[1][1];
        arrX[0] = (arrB[0] - arrX[1] * arrA[0][1] - arrX[2] * arrA[0][2] - arrX[3] * arrA[0][3]) / arrA[0][0];

        if (ch1 != 0 || ch2 != 0) {
            temp = arrX[ch1];
            arrX[ch1] = arrX[ch2];
            arrX[ch2] = temp;
        }

        //проверка решения на существование
        for (auto i: arrX)
            if (i == INFINITY || i != i) {
                answ = false;
            };
        if (!answ) {
            cout << "Warning! Solution not found" << endl;
        } else {
            for (int i = 0; i < 4; i++) cout << "X[" << i << "] = " << arrX[i] << endl;
            cout << endl;

            // ищем обратную матрицу
            cout << "-----------Second part-----------------" << endl;

            cout << endl;

            // единичная матрица для получения обратной
            setupOnesOnMainDiagonal(size, arrOnes);

            //выводим обе матрицы
            cout << "Base mt and Mt of ones" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) cout << arrCopy[i][j] << " ";

                cout << " | ";

                for (int j = 0; j < 4; j++) cout << arrOnes[i][j] << " ";

                cout << endl;
            }

            for (int col = 0; col < size; col++) {
                maxElement = arrCopy[col][col];
                maxRow = col;

                //находим главный элемент
                for (int row = col; row < size; row++) {
                    if (maxElement >= arrCopy[row][col]) {//если больше - ничего не происходит
                    } else {
                        maxElement = arrCopy[row][col];
                        maxRow = row;
                    }
                }

                //перестановка строк поля row и col меняются местами, т.к.
                //меняем местами ряды, а не колонки
                for (int iterator = 0; iterator < size; iterator++) {
                    temp = arrCopy[col][iterator];
                    arrCopy[col][iterator] = arrCopy[maxRow][iterator];
                    arrCopy[maxRow][iterator] = temp;

                    temp = arrOnes[col][iterator];
                    arrOnes[col][iterator] = arrOnes[maxRow][iterator];
                    arrOnes[maxRow][iterator] = temp;
                }
            }

            cout << "Upper triangle" << endl;//получение верхнетреугольной матрицы
            for (int col = 0; col < size - 1; col++) {
                for (int row = col + 1; row < size; row++) {
                    float del = arrCopy[row][col] / arrCopy[col][col];
                    for (int el = 0; el < size; el++) {
                        arrCopy[row][el] = arrCopy[row][el] - arrCopy[col][el] * del;

                        arrOnes[row][el] = arrOnes[row][el] - arrOnes[col][el] * del;
                    }
                }

                //выбор главного элемента по столбцам

                int nextRow = col + 1;

                maxElement = arrCopy[nextRow][nextRow];

                if (maxElement == 0) {
                    maxCol = nextRow;
                    for (int col2 = nextRow; col2 < 4; col2++) {

                        if (abs(maxElement) >= abs(arrCopy[nextRow][col2])) {//если больше - ничего не происходит
                        } else {
                            maxElement = arrCopy[nextRow][col2];
                            maxCol = col2;
                            ch1 = nextRow;
                            ch2 = maxCol;
                        }
                    }

                    //перестановка строк поля row и col меняются местами, т.к.
                    //меняем местами ряды, а не колонки
                    for (int iterator = 0; iterator < size; iterator++) {
                        temp = arrCopy[iterator][nextRow];
                        arrCopy[iterator][nextRow] = arrCopy[iterator][maxCol];
                        arrCopy[iterator][maxCol] = temp;

                        temp = arrOnes[iterator][nextRow];
                        arrOnes[iterator][nextRow] = arrOnes[iterator][maxCol];
                        arrOnes[iterator][maxCol] = temp;
                    }
                }
            }

            //выводим обе матрицы
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) cout << arrCopy[i][j] << " ";

                cout << " | ";

                for (int j = 0; j < 4; j++) cout << arrOnes[i][j] << " ";

                cout << endl;
            }
            cout << endl;

            //приводим к единицам на главной диагонали
            cout << "Ones on the main line" << endl;
            for (int i = 0; i < size; i++) {
                float del = arrCopy[i][i];
                for (int j = 0; j < size; j++) {
                    arrCopy[i][j] = arrCopy[i][j] / del;
                    arrOnes[i][j] = arrOnes[i][j] / del;
                }
            }

            //выводим обе матрицы
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) cout << arrCopy[i][j] << " ";

                cout << " | ";

                for (int j = 0; j < size; j++) cout << arrOnes[i][j] << " ";

                cout << endl;
            }
            cout << endl;

            //приводим к единичной матрице
            cout << "Matrix of ones" << endl;
            for (int counter = size - 1; counter > 0; counter--) {
                for (int i = counter - 1; i > -1; i--) {
                    float del = arrCopy[i][counter] / arrCopy[counter][counter];
                    for (int j = 3; j > -1; j--) {
                        arrCopy[i][j] = arrCopy[i][j] - arrCopy[counter][j] * del;
                        arrOnes[i][j] = arrOnes[i][j] - arrOnes[counter][j] * del;
                    }
                }
            }

            //выводим обе матрицы
            printMatrix(arrCopy, arrOnes);

            //обратная матрица
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) cout << arrOnes[i][j] << " ";
                cout << endl;
            }
        }

    }
    return 0;

}

/**
 * Инициализирует массив с возрастанием элементов
 * @param length длина массива
 * @param arrB массив котоый инициализируем
 */
void setupArr(int length, float array[]) {
    for (int i = 0; i < length; i++) {
        array[i] = i + 1;
    }
}

/**
 * Инициализирует массив из 1
 * @param length длина
 * @param array сам массив
 */
void setupArrOnes(int length, float array[]) {
    for (int i = 0; i < length; i++) {
        array[i] = 1;
    }
}

/**
 * Устанавливает 1 на главную диагональ
 * @param length длина массива
 * @param array двумерный массив
 */
void setupOnesOnMainDiagonal(int length, float array[][size]) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            array[i][j] = 0;
            array[i][i] = 1;
        }
    }
}

/**
 * Устанавливает 1-4 на главную диагональ
 * @param length длина массива
 * @param array двумерный массив
 */
void setupOnMainDiagonal(int length, float array[][size]) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            array[i][j] = 0;
            array[i][i] = i + 1;
        }
    }
}

/**
 * Устанавливает 1-4 на побочную диагональ
 * @param length длина массива
 * @param array двумерный массив
 */
void setupOnSecondaryDiagonal(int length, float array[][size]) {
    for (int i = length - 1; i > -1; i--) {
        for (int j = 0; j < length; j++) {
            array[i][j] = 0;
            array[i][3 - i] = i + 1;
        }
    }
}

/**
 * Создает копию матрицы
 * @param array1
 * @param array2
 */
void copyMatrix(float array1[][size], float array2[][size]) {
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            array1[row][col] = array2[row][col];
}

/**
 * Выводит в консоль матрицы
 * @param array1 одномерная матрицы
 * @param array2 двумерная матрица
 */
void printMatrix(float array1[], float array2[][size]) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) cout << array2[row][col] << " ";
        cout << " | " << array1[row] << endl;
    }
    cout << endl;
}
/**
 * Выводит в консоль матрицы
 * @param array1 двумарная матрица
 * @param array2 дыумерная матрица
 */
void printMatrix(float array1[][size], float array2[][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) cout << array1[i][j] << " ";
        cout << " | ";
        for (int j = 0; j < size; j++) cout << array2[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}


/**
 * Выбор главного элемента по строкам
 * @param array1
 * @param array2
 */
void changeLines(float array1[], float array2[][size]) {
    for (int col = 0; col < size; col++) {
        maxElement = array2[col][col];
        maxRow = col;
        //находим главный элемент
        for (int row = col; row < size; row++) {
            if (maxElement >= array2[row][col]) {//если больше - ничего не происходит
            } else {
                maxElement = array2[row][col];
                maxRow = row;
            }
        }
        //перестановка строк поля row и col меняются местами, т.к.
        //меняем местами ряды, а не колонки
        for (int iterator = 0; iterator < size; iterator++) {
            temp = array2[col][iterator];
            array2[col][iterator] = array2[maxRow][iterator];
            array2[maxRow][iterator] = temp;
        }
        temp = array1[col];
        array1[col] = array1[maxRow];
        array1[maxRow] = temp;
    }
}

/**
 * Получение верхнетреугольной матрицы
 * @param array1
 * @param array2
 */
void upperTriangle(float array1[], float array2[][size]) {
    for (int col = 0; col < size - 1; col++) {
        for (int row = col + 1; row < size; row++) {
            float del = array2[row][col] / array2[col][col];
            for (int el = 0; el < size; el++) {
                array2[row][el] = array2[row][el] - array2[col][el] * del;
            }
            array1[row] = array1[row] - array1[col] * del;
        }
        //выбор главного элемента по столбцам
        int nextRow = col + 1;
        maxElement = array2[nextRow][nextRow];
        if (maxElement == 0) {
            cout << "Found zero on the main line" << endl;
            maxCol = nextRow;
            for (int col2 = nextRow; col2 < size; col2++) {
                if (abs(maxElement) >= abs(array2[nextRow][col2])) {}
                else {
                    maxElement = array2[nextRow][col2];
                    maxCol = col2;
                    ch1 = nextRow;
                    ch2 = maxCol;
                }
            }
            //перестановка строк поля row и col меняются местами, т.к.
            //меняем местами ряды, а не колонки
            for (int iterator = 0; iterator < size; iterator++) {
                temp = array2[iterator][nextRow];
                array2[iterator][nextRow] = array2[iterator][maxCol];
                array2[iterator][maxCol] = temp;
            }
            temp = array1[col];
            array1[col] = array1[maxCol];
            array1[maxCol] = temp;
        }
    }
}
