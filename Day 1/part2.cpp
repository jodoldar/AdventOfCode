/**
 * @file part2.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 1 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> vGetNumbersInFile(string sFileName){
    ifstream fInputFile;
    string sLine;
    vector<int> lNumbervector;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
           lNumbervector.push_back(stoi(sLine));
        }

        fInputFile.close();
    }
    else
    {
        cout << "Error opening " << sFileName << " file." << endl;
    }

    return lNumbervector;
}

int main(int argc, char const *argv[])
{
    int iPrevValue, iCurrValue;
    int iNumOfIncreases = 0;
    vector<int> vNumberList;

    vNumberList = vGetNumbersInFile("input.txt");

    if (vNumberList.size() < 4)
    {
        cerr << "Not enough numbers to detect increases." << endl;
        return 1;
    }

    for (size_t i = 3; i < vNumberList.size(); i++)
    {
        iPrevValue = 0;
        iCurrValue = 0;

        for (size_t iFirst = i-3; iFirst < i; iFirst++)
        {
            iPrevValue += vNumberList[iFirst];
        }

        for (size_t iSecond = i-2; iSecond <= i; iSecond++)
        {
            iCurrValue += vNumberList[iSecond];
        }

        if (iCurrValue > iPrevValue)
        {
            iNumOfIncreases++;
        }
    }

    cout << "Number of increases: " << iNumOfIncreases << endl;

    return 0;
}
