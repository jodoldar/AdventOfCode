/**
 * @file part2.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 3 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
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

int bin2dec(string number)
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

vector<vector<int>> getFilteredBlocks(vector<vector<int>> vCurrentStatus, int iCol, int iMostRepeated)
{
    vector<vector<int>> vTempStruct;

    for (size_t iRow = 0; iRow < vCurrentStatus[0].size(); iRow++)
    {
        if (vCurrentStatus[iCol][iRow] == iMostRepeated)
        {
            for (size_t iNewCol = 0; iNewCol < vCurrentStatus.size(); iNewCol++)
            {
                if (vTempStruct.size() == iNewCol)
                {
                    vTempStruct.push_back(vector<int>());
                }
                vTempStruct[iNewCol].push_back(vCurrentStatus[iNewCol][iRow]);
            }
        }
    }

    return vTempStruct;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> binaryCodes;
    int iOneOccurrences, iZeroOccurrences;
    string sFinalNumber = "";
    string sFinalNumberNeg = "";
    vector<vector<int>> vFilteredCodes;
    vector<vector<int>> vFilteredCodesNeg;

    if (!siReadAndProcessInput("input.txt", binaryCodes))
    {
        cout << "Read " << binaryCodes[0].size() << " lines." << endl;
        vFilteredCodes = binaryCodes;
        vFilteredCodesNeg = binaryCodes;

        for (size_t iCol = 0; iCol < binaryCodes.size() && vFilteredCodes[0].size()>1; iCol++)
        {
            iOneOccurrences = accumulate(vFilteredCodes[iCol].begin(), vFilteredCodes[iCol].end(), 0, [](int a, int b){return a + b;});
            iZeroOccurrences = vFilteredCodes[0].size() - iOneOccurrences;
            if (iOneOccurrences >= iZeroOccurrences)
            {
                /* Most common is 1 */
                vFilteredCodes = getFilteredBlocks(vFilteredCodes, iCol, 1);
            }
            else
            {
                /* Most common is 0 */
                vFilteredCodes = getFilteredBlocks(vFilteredCodes, iCol, 0);
            }
        }

        for (size_t iCol = 0; iCol < binaryCodes.size() && vFilteredCodesNeg[0].size()>1; iCol++)
        {
            iOneOccurrences = accumulate(vFilteredCodesNeg[iCol].begin(), vFilteredCodesNeg[iCol].end(), 0, [](int a, int b){return a + b;});
            iZeroOccurrences = vFilteredCodesNeg[0].size() - iOneOccurrences;
            if (iZeroOccurrences <= iOneOccurrences)
            {
                /* Least common is 1 */
                vFilteredCodesNeg = getFilteredBlocks(vFilteredCodesNeg, iCol, 0);
            }
            else
            {
                /* Least common is 0 */
                vFilteredCodesNeg = getFilteredBlocks(vFilteredCodesNeg, iCol, 1);
            }
        }

        for (auto &&head : vFilteredCodes)
        {
            sFinalNumber.append(to_string(head[0]));
        }
        for (auto &&head : vFilteredCodesNeg)
        {
            sFinalNumberNeg.append(to_string(head[0]));
        }

        cout << "Final numbers are: \n\t" << sFinalNumber << " -> " << bin2dec(sFinalNumber) << "\n\t" <<
            sFinalNumberNeg << " -> " << bin2dec(sFinalNumberNeg) << "\n\t" <<
            "-> " << bin2dec(sFinalNumber)*bin2dec(sFinalNumberNeg) << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
