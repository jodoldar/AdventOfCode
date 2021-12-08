/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 5 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
    }
    else
    {
        return 1;
    }

    return 0;
}
