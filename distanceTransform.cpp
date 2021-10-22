/**
 * File: dt.cpp
 *
 * Implementation of the Distance Transform algorithm in 2D. This code template
 * accompanies the in-class activity on Oct 13th, 2021 for ROB 102.
 **/

#include <iostream>
#include <vector>
#include <cmath>

#define HIGH 1e6;

struct Cell
{
    int i, j;  // row, col
};

template <class T>
void printVector(std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

template <class T>
void printMatrix(std::vector<T>& m, int width, int height)
{
    int idx = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << m[idx] << "  ";
            idx++;
        }
        std::cout << "\n";
    }
}

int cellToIdx(int i, int j, int h, int w)
{
    int idx = -1;
    // TODO (if needed): Convert a cell coordinate to an index.
    return idx;
}

Cell idxToCell(int idx, int h, int w)
{
    Cell c;
    // TODO (if needed): Convert an index to a cell coordinate.
    return c;
}

std::vector<float> distanceTransform1D(std::vector<int>& map)
{
    int N = map.size();
    std::vector<float> dt(N, 1000);
    std::vector<float> dcompare(N, 1000);
    float minF = 1000;  // mins fixes end indices being 0
    float minB = 1000;
    for (int i=0;i<N;i++){ // populates dt that traverses forward
        if (map[i]==1){
            dt[i]=0;
            minF=0;
        }
        else {
            minF++;
            dt[i]=minF;
        }
    }
    for (int i=N-1;i>=0;i--){ // populates dcompare, a vector that traverses backward
        if (map[i]==1){
            dcompare[i]=0;
            minB = 0;
        }
        else {
            minB++;
            dcompare[i]=minB;
        }
    }
    for (int i=0;i<N;i++){ // takes the lowest value of each of the two indices
        if (dcompare[i]<dt[i]){
            dt[i]=dcompare[i];
        }
    }
    return dt;
}

std::vector<float> distanceTransform2D(std::vector<int>& map,
                                       int height, int width)
{
    int N = width * height;
    std::vector<float> dt(N, 0);
    
    // for (int i; i<N; N++) {
    //     dt[i] = abs() + abs();
    // }

    // TODO: Implement the 2D Manhattan distance transform of a binary map.

    return dt;
}

int main() {
    // 1D distance transform.
    // TODO: Try different maps!
    std::vector<int> map1D = {0, 0, 1, 0, 1};
    std::vector<float> dt1D = distanceTransform1D(map1D);

    std::cout << "Map:\n";
    printVector(map1D);
    std::cout << "\n1D Distance Transform:\n";
    printVector(dt1D);
    std::cout << "\n";

    // 2D L1 distance transform.
    // TODO: Try different maps!
    int width = 5, height = 5;
    std::vector<int> map2D = {0, 0, 0, 0, 0,
                              0, 0, 0, 0, 1,
                              1, 1, 1, 0, 1,
                              0, 0, 0, 0, 1,
                              0, 0, 0, 0, 1};
    if (map2D.size() != width * height)
    {
        std::cerr << "Map has wrong size " << map2D.size() << "\n";
        return -1;
    }

    std::vector<float> dt2D = distanceTransform2D(map2D, height, width);

    std::cout << "2D Map:\n";
    printMatrix(map2D, width, height);
    std::cout << "2D Manhattan Distance Transform:\n";
    printMatrix(dt2D, width, height);
}