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
    cout << "\nWith type " << iType << ", Vec: [";
    for (auto &&i : vecElems)
    {
        cout << i << ",";
    }
    cout << "\b]";

    switch (iType)
    {
    case 0:
        return accumulate(vecElems.begin(), vecElems.end(), 0);
    case 1:
        return accumulate(vecElems.begin(), vecElems.end(), 1, multiplies<int64_t>());
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
    //cout << "\nDetected packet with Version: " << iVersion << " and Type: " << iType;

    if (iType != 4)
    {   /* It's an operator */
        int iLenType = bin2dec(sPacket.substr(6,1));
        //cout << "\tLenType is " << iLenType;

        /* List of subpackets values */
        vector<int64_t> vecElements;

        if (iLenType == 0)
        {
            int iSubPacketLen = bin2dec(sPacket.substr(7,15));
            //cout << "\tSubPacket length is " << iSubPacketLen;

            int iInternalLen = 0;
            int64_t iReturnedVal = 0;

            while (iInternalLen < iSubPacketLen) {
                iInternalLen += processPacket(sPacket.substr(22+iInternalLen), iReturnedVal);
                if (iReturnedVal != INT64_MAX)
                    vecElements.push_back(iReturnedVal);
            }

            //cout << "Finished subPacket with len " << iInternalLen;

            result = calculateResult(vecElements, iType);
            cout << " Result is " << result << endl;

            return 22+iSubPacketLen;
        }
        else
        {
            int iNumOfSubPackets = bin2dec(sPacket.substr(7,11));
            //cout << "\tNum of subPackets is " << iNumOfSubPackets;

            int iStartPos = 18;
            int64_t iReturnedVal = 0;
            for (size_t i = 0; i < iNumOfSubPackets; i++)
            {
                //cout << "\tCheck SubPacket at " << iStartPos;
                iStartPos+= processPacket(sPacket.substr(iStartPos), iReturnedVal);

                if (iReturnedVal != INT64_MAX)
                    vecElements.push_back(iReturnedVal);
            }

            result = calculateResult(vecElements, iType);
            cout << " Result is " << result << endl;

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

        cout << "\tNumber in packet is " << result << "\tSize is " << iLiteralPos;

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

    cout << "Size of int64 is " << sizeof(int64_t) << endl;
    cout << "Size of intmax is " << sizeof(intmax_t) << endl;
    cout << "Size of int is " << sizeof(int) << endl;
    cout << "Size of long is " << sizeof(long) << endl;
    cout << "Size of long long is " << sizeof(long long) << endl;

    return 0;
}
