/**
 * @file part2.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 5 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "../Common/utils.hpp"

using namespace std;

class Point
{
public:
    int x,y;

    Point(int xIn, int yIn) : x(xIn), y(yIn) {};
    Point(string coords);
};

Point::Point(string coords)
{
    size_t zPos = coords.find(",");

    if (zPos != string::npos)
    {
        x = stoi(coords.substr(0,zPos));
        y = stoi(coords.erase(0,zPos+1));
    }
}

class VentMap
{
public:
    int occurrences[999][999] = {};

    VentMap(){};
    void addLine(Point p1, Point p2);
    int getDangerousPoints();
    void toPgmFile(string filename);

    friend ostream& operator<<(ostream& os, const VentMap& obj);
};

void VentMap::addLine(Point p1, Point p2)
{
    /* Check horizontal or vertical */
    if (p1.x == p2.x)
    {
        /* Vertical line */
        if (p1.y > p2.y)
        {
            for (size_t iCol = p1.y; iCol >= p2.y; iCol--)
            {
                occurrences[p1.x][iCol]++;
            }
        }
        else
        {
            for (size_t iCol = p1.y; iCol <= p2.y; iCol++)
            {
                occurrences[p1.x][iCol]++;
            }
        }
    }
    else if (p1.y == p2.y)
    {
        /* Horizontal line */
        if (p1.x > p2.x)
        {
            for (size_t iRow = p1.x; iRow >= p2.x; iRow--)
            {
                occurrences[iRow][p1.y]++;
            }
        }
        else
        {
            for (size_t iRow = p1.x; iRow <= p2.x; iRow++)
            {
                occurrences[iRow][p1.y]++;
            }
        }
    }
    else if (abs(p1.x - p2.x) == abs(p1.y - p2.y))
    {
        /* Diagonal line */
        if ((p1.x > p2.x) && (p1.y > p2.y))
        {
            /* <\ */
            for (size_t iRow = p1.x, iCol = p1.y; iRow >= p2.x; iRow--, iCol--)
            {
                occurrences[iRow][iCol]++;
            }
        }
        else if ((p1.x > p2.x) && (p1.y < p2.y))
        {
            /* </ */
            for (size_t iRow = p1.x, iCol = p1.y; iRow >= p2.x; iRow--, iCol++)
            {
                occurrences[iRow][iCol]++;
            }
        }
        else if ((p1.x < p2.x) && (p1.y > p2.y))
        {
            /* /> */
            for (size_t iRow = p1.x, iCol = p1.y; iRow <= p2.x; iRow++, iCol--)
            {
                occurrences[iRow][iCol]++;
            }
        }
        else if ((p1.x < p2.x) && (p1.y < p2.y))
        {
            /* \> */
            for (size_t iRow = p1.x, iCol = p1.y; iRow <= p2.x; iRow++, iCol++)
            {
                occurrences[iRow][iCol]++;
            }
        }
    }
}

int VentMap::getDangerousPoints()
{
    int iPointCounter = 0;

    for (size_t iRow = 0; iRow < 999; iRow++)
    {
        for (size_t iCol = 0; iCol < 999; iCol++)
        {
            if (occurrences[iRow][iCol] > 1)
            {
                iPointCounter++;
            }
        }
    }

    return iPointCounter;
}

ostream& operator<<(ostream& os, const VentMap& obj)
{
    os << "\t";
    for (size_t i1 = 0; i1 < 999; i1++)
    {
        os << " " << i1;
    }
    os << "\n";

    for (size_t iRow = 0; iRow < 999; iRow++)
    {
        os << iRow << " ";
        for (size_t iCol = 0; iCol < 999; iCol++)
        {
            os << obj.occurrences[iRow][iCol] << " ";
        }
        os << "\n";
    }

    return os;
}

void VentMap::toPgmFile(string filename)
{
    ofstream oImageFile;
    oImageFile.open(filename, ios_base::binary | ios_base::out);

    if (oImageFile.is_open())
    {
        int max_elem = 0;
        for (size_t iRow = 0; iRow < 999; iRow++)
            for (size_t iCol = 0; iCol < 999; iCol++)
                max_elem = max(occurrences[iRow][iCol], max_elem);

        oImageFile << "P2\n999 999\n" << max_elem << endl;

        for (size_t iRow = 0; iRow < 999; iRow++)
        {
            for (size_t iCol = 0; iCol < 999; iCol++)
            {
                oImageFile << max_elem - occurrences[iRow][iCol] << " ";
            }
            oImageFile << endl;
        }
        oImageFile.close();
    }
}

short int siReadAndProcessInput(string sFileName, VentMap &vMap)
{
    ifstream fInputFile;
    string sLine;
    string sPoint1, sPoint2;
    size_t zPos;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
            {
                continue;
            }

            zPos = sLine.find("->");
            sPoint1 = sLine.substr(0, zPos); trim(sPoint1);
            sPoint2 = sLine.erase(0, zPos+2); trim(sPoint2);

            vMap.addLine(Point(sPoint1), Point(sPoint2));
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

int main(int argc, char const *argv[])
{
    VentMap vMap;

    if (!siReadAndProcessInput("input.txt", vMap))
    {
        cout << "Processed file. There are " << vMap.getDangerousPoints() << " dangerous points." << endl;

        vMap.toPgmFile("vent_map.pgm");
    }
    else
    {
        return 1;
    }

    return 0;
}
