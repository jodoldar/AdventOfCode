/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 3 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

short int siReadAndProcessInput(string sFileName, vector<vector<int>> &vCodes)
{
    ifstream fInputFile;
    string sLine;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            for (int iPos = 0 ; iPos < sLine.size(); iPos++)
            {
                if (vCodes.size() == iPos)
                {
                    vCodes.push_back(vector<int>());
                }
                vCodes[iPos].push_back(sLine[iPos]-'0');
            }
        }

        fInputFile.close();
    }
    else
    {
        cout << "Error opening " << sFileName << " file." << endl;
        return 1;
    }

    return 0;
}

int bin2decGam(string number)
{
    int ret_value = 0;
    int base = 1;

    for (int i = number.length() - 1; i >= 0; i--)
    {
        if (number[i] == '1')
        {
            ret_value += base;
        }
        base *= 2;
    }

    return ret_value;
}

int bin2decEps(string number)
{
    int ret_value = 0;
    int base = 1;

    for (int i = number.length() - 1; i >= 0; i--)
    {
        if (number[i] == '0')
        {
            ret_value += base;
        }
        base *= 2;
    }

    return ret_value;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> binaryCodes;
    int iOneOccurrences;
    string sFinalNumber = "";

    if (!siReadAndProcessInput("input.txt", binaryCodes))
    {
        cout << "Read " << binaryCodes[0].size() << " lines." << endl;

        for (size_t iCol = 0; iCol < binaryCodes.size(); iCol++)
        {
            iOneOccurrences = accumulate(binaryCodes[iCol].begin(), binaryCodes[iCol].end(), 0, [](int a, int b){return a + b;});
            if (iOneOccurrences > (binaryCodes[0].size()/2))
            {
                sFinalNumber.append("1");
            }
            else
            {
                sFinalNumber.append("0");
            }
        }

        cout << "Final number is: " << sFinalNumber << " -> " << bin2decGam(sFinalNumber) << "," << bin2decEps(sFinalNumber) 
            << " -> " << bin2decGam(sFinalNumber)*bin2decEps(sFinalNumber) << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
