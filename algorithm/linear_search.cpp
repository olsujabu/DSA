/*
author : Buyandelger.J
date : 28/07/2025 23:01
title : Linear Search Algorithm
*/

#include <iostream> // default library of C++
#include <stdlib.h> // for random number
#include <ctime>    // for random number
#include <chrono>   // for execution
#include <iomanip>  // for set precision

using namespace std;
using namespace chrono;

int main()
{
    auto start = high_resolution_clock::now();
    srand(time(0));
    int random_num = (rand() % 100 + 1);
    for (int i = 1; i <= 100; i++)
    {
        if (i == random_num)
        {
            cout << "I number was " << random_num << "\n";
            auto end = high_resolution_clock::now();
            duration<double> elapsed = end - start;
            cout << fixed << setprecision(7);
            cout << "Time taken: " << elapsed.count() << " seconds\n";
        }
        else
            continue;
    }
    return 0;
}