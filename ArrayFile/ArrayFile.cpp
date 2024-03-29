﻿// ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

typedef double* pDouble;
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0;
    do {
        cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return size;
}

/*
*   RndInputArrayDouble
*
*/
int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        cout << A[i] << "   ";
    }
    return size;
}

int ConsoleInputDynamicArrayNew(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

void ConsoleInputVector(int sizeMax, vector<double>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return;
}


/*
*  WriteArrayTextFile
*
*/

void WriteArrayTextFile(int n, double* arr, const char* fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;
    fin >> size;
    if (size <= 0) return 0;
    if (size > n) size = n;
    for (int i = 0; i < n; i++)
        fin >> arr[i];
    fin.close();
    return size;

}


void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&n, sizeof(int));
    std::streamsize  cn = static_cast<std::streamsize>(n) * sizeof(double);
    bfout.write((const char*)arr, cn);
    bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
}

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Local array  \n";
    cout << "    2.  Dynamic array 1 \n";
    cout << "    3.  Dynamic array 2  new \n";
    cout << "    4.  Dynamic array : vector \n";
    cout << "    5.  Exit \n";
}
void WriteArraysTextFile(int x1, int x2, double* a, double* b, const char* t)
{
    ofstream fout(t);
    if (fout.fail()) return;
    fout << x1 << endl;
    
    for (int i = 0; i < x1; i++)
        fout << a[i] << "   ";
    fout << endl;
    for (int i = 0; i < x2; i++)
        fout << b[i] << "   ";
    fout.close();
}
void MenuInput()
{
    cout << "     Menu Input   \n";
    cout << "    1.  Console all \n";
    cout << "    2.  Console - size, array - random \n";
    cout << "    3.  File 1.txt \n";
    cout << "    4.  bb    \n";
    cout << "    5.  Exit \n";
}
const int MAX_SIZE = 400;
void Task1()
{
    int n, j = 0;
    double A[MAX_SIZE], B[MAX_SIZE];
   

    n = ConsoleInputArray(MAX_SIZE, A);
    WriteArrayBinFile(n, A, "Write.bin");
    WriteArrayTextFile(n, A, "Write.txt");
    WriteArrayBinFile(n, A, "Read.bin");
    WriteArrayBinFile(n, A, "Read.bin");

    for (int i = 0; i < n; i++)
        if (A[i] != 0) 
            B[j++] = A[i];
    WriteArrayBinFile(j, B, "Write.bin");
    WriteArrayTextFile(j, B, "Write.txt");
    WriteArrayBinFile(j, B, "Read.bin");
    WriteArrayBinFile(j, B, "Read.bin");
    WriteArraysTextFile(n, j, A, B, "Write.txt");

    cout << "Array B witout zero elements: ";
    for (int i = 0; i < j; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
}

void Task2()
{
    int n;
    double A[MAX_SIZE], x;
    n = ConsoleInputArray(MAX_SIZE, A);
    cout << "Input X: ";
    cin >> x;
    int max_negative = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (*(A + i) < 0 && *(A + i) > max_negative && *(A + i) < x) {
            max_negative = *(A + i);
        }
        if (*(A + i) < x) {
            break;
        }
    }

    if (max_negative == INT_MIN) {
        cout << "No negative elements!" << endl;
    }
    else {
        cout << "Max negative element: " << max_negative << endl;
    }
}
void Task3() {
    int n;
    double A[MAX_SIZE];
    double sum = 0;
    double avg;

    cout << "Input n (n <= 200): ";
    cin >> n;

    cout << "Input array A(2n): " << endl;
    for (int i = 0; i < 2 * n; i++) {
        cout << "Array[ " << i << "] ";
        cin >> A[i];
        if (i < n) {
            sum += A[i];
        }
    }

    avg = sum / n;

    sum = 0;
    for (int i = n; i < 2 * n; i++) {
        if (A[i] > avg) {
            sum += A[i];
        }
    }


    cout << "Sum: " << sum << endl;
}
int main()
{
    ShowMainMenu();
    int nom;
    do {
        cin >> nom;
    } while (nom < 1 || nom > 3);
    system("CLS");
    switch (nom)
    {
    case 1:
    {
        Task1();
    }
    break;
    case 2:
    {
        Task2();
    }
    break;
    case 3:
    {
        Task3();
    }
    break;
    default:
        break;
    }
    return 1;
}