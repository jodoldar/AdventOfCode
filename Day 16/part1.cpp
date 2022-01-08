/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 16 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <cctype>
#include <climits>
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

int processPacket(string sPacket, int iPos)
{
    int iVersion = bin2dec(sPacket.substr(iPos,3));
    iVersionCount += iVersion;
    int iType = bin2dec(sPacket.substr(iPos+3,3));
    cout << "\nDetected patcket with Version: " << iVersion << " and Type: " << iType;

    if (iType != 4)
    {
        int iLenType = bin2dec(sPacket.substr(iPos+6,1));
        cout << "\tLenType is " << iLenType;

        if (iLenType == 0)
        {
            int iSubPacketLen = bin2dec(sPacket.substr(iPos+7,15));
            cout << "\tSubPacket length is " << iSubPacketLen;

            int iInternalLen = 0;

            while (iInternalLen < iSubPacketLen)
                iInternalLen += processPacket(sPacket, iPos+22+iInternalLen);

            cout << "Finished subPacket with len " << iInternalLen;

            return 22+iInternalLen;
        }
        else
        {
            int iNumOfSubPackets = bin2dec(sPacket.substr(iPos+7,11));
            cout << "\tNum of subPackets is " << iNumOfSubPackets;

            int iStartPos = iPos+18;
            for (size_t i = 0; i < iNumOfSubPackets; i++)
            {
                cout << "\tCheck SubPacket at " << iStartPos;
                iStartPos+= processPacket(sPacket, iStartPos);
            }

            return 18+iStartPos;
        }
    }
    else
    {
        int iLiteralPos = iPos + 6;
        int iFinalPadding = 0;
        string sNumber = "";

        while (true)
        {
            sNumber.append(sPacket.substr(iLiteralPos+1,4));

            iLiteralPos += 5;

            if (sPacket[iLiteralPos-5]=='0')
                break;
        }

        cout << "\tNumber in packet is " << bin2dec(sNumber) << "\tSize is " << iLiteralPos - iPos << endl;


        return iLiteralPos - iPos;
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{
    string sPacket;

    if (!siReadAndProcessInput("input.txt", sPacket))
    {
        cout << "Packet to process is: " << sPacket << endl;
        iVersionCount = 0;

        processPacket(sPacket, 0);

        cout << "\nTotal versions account is " << iVersionCount << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
