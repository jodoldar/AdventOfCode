/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 16 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

const string RED_COLOR = "\033[31m";
const string RESET_COLOR = "\033[0m";

int iVersionCount;

short int siReadAndProcessInput(string sFileName, string &sPacket)
{
    ifstream fInputFile;
    string sLine;
    int iLineX = 0, iLineY = 0;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        getline(fInputFile, sLine);

        if (sLine.empty())
        {
            fInputFile.close();
            return 1;
        }

        for (auto &&letter : sLine)
        {
            sPacket.append(char_to_bin(letter));
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

int64_t calculateResult(vector<int64_t> vecElems, int iType)
{
    switch (iType)
    {
    case 0:
        return accumulate(vecElems.begin(), vecElems.end(), (int64_t)0);
    case 1:
        return accumulate(vecElems.begin(), vecElems.end(), (int64_t)1, multiplies<int64_t>());
    case 2:
        return *min_element(vecElems.begin(), vecElems.end());
    case 3:
        return *max_element(vecElems.begin(), vecElems.end());
    case 5:
        return vecElems[0] > vecElems[1] ? 1 : 0;
    case 6:
        return vecElems[0] < vecElems[1] ? 1 : 0;
    case 7:
        return vecElems[0] == vecElems[1] ? 1 : 0;
    default:
        return -1;
    }
}

int processPacket(string sPacket, int64_t& result)
{
    result = 0;

    int iVersion = bin2dec(sPacket.substr(0,3));
    iVersionCount += iVersion;
    int iType = bin2dec(sPacket.substr(3,3));

    if (iType != 4)
    {   /* It's an operator */
        int iLenType = bin2dec(sPacket.substr(6,1));

        /* List of subpackets values */
        vector<int64_t> vecElements;

        if (iLenType == 0)
        {
            int iSubPacketLen = bin2dec(sPacket.substr(7,15));

            int iInternalLen = 0;
            int64_t iReturnedVal = 0;

            while (iInternalLen < iSubPacketLen) {
                iInternalLen += processPacket(sPacket.substr(22+iInternalLen), iReturnedVal);
                if (iReturnedVal != INT64_MAX)
                    vecElements.push_back(iReturnedVal);
            }

            result = calculateResult(vecElements, iType);

            return 22+iSubPacketLen;
        }
        else
        {
            int iNumOfSubPackets = bin2dec(sPacket.substr(7,11));

            int iStartPos = 18;
            int64_t iReturnedVal = 0;
            for (size_t i = 0; i < iNumOfSubPackets; i++)
            {
                iStartPos+= processPacket(sPacket.substr(iStartPos), iReturnedVal);

                if (iReturnedVal != INT64_MAX)
                    vecElements.push_back(iReturnedVal);
            }

            result = calculateResult(vecElements, iType);

            return iStartPos;
        }
    }
    else    /* It's a literal */
    {
        int iLiteralPos = 6;
        string sNumber = "";

        while (true)
        {
            sNumber.append(sPacket.substr(iLiteralPos+1,4));

            iLiteralPos += 5;

            if (sPacket[iLiteralPos-5]=='0')
                break;
        }

        result = bin2dec(sNumber);

        return iLiteralPos;
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{
    string sPacket;
    int64_t iAcumulatedValue = 0;

    if (!siReadAndProcessInput("input.txt", sPacket))
    {
        cout << "Packet to process is: " << sPacket << endl;
        iVersionCount = 0;

        processPacket(sPacket, iAcumulatedValue);

        cout << "\nTotal versions account is " << iVersionCount << endl;
        cout << "Accumulated value is " << iAcumulatedValue << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
