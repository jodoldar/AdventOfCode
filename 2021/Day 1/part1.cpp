/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 1 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream fInputFile;
    string sLine;
    int iPrevValue, iCurrValue;
    int iNumOfIncreases = 0;
    unsigned uLineCounter = 1;

    fInputFile.open("input.txt", ios::in);

    if (fInputFile.is_open())
    {
        /* Get first line */
        getline(fInputFile, sLine);

        if (sLine.empty())
        {
            cout << "Error processing the first line of the file" << endl;
            return 1;
        }

        /* Extract first value */
        iPrevValue = stoi(sLine);

        while (!fInputFile.eof())
        {
            uLineCounter++;
            getline(fInputFile, sLine);

            if (sLine.empty())
            {
                cout << "Error processing the line " << uLineCounter << " of the file" << endl;
                continue;
            }

            iCurrValue = stoi(sLine);

            if (iCurrValue > iPrevValue)
            {
                iNumOfIncreases++;
            }

            iPrevValue = iCurrValue;
        }

        cout << "Number of increases: " << iNumOfIncreases << endl;

        /* End file operations */
        fInputFile.close();
    }
    else
    {
        cout << "Error opening input.txt file." << endl;
        return 1;
    }

    return 0;
}
