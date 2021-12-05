/**
 * @file part1.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 4 - Part 1 of the Advent of Code 2021
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
#include <vector>

using namespace std;

class Cardboard
{
public:
    int numbers[5][5];
    bool marked[5][5];
    int iCurrentInputRow;
    int iCurrentInputCol;

    Cardboard(){
        iCurrentInputRow = 0;
        iCurrentInputCol = 0;
    };

    ~Cardboard(){};
    bool isWinner();
    int getScore(int lastNumber);
    void checkNumber(int number);
};

bool Cardboard::isWinner()
{
    bool bTemp;

    for (size_t iRow = 0; iRow < 5; iRow++)
    {
        bTemp = true;
        for (size_t iCol = 0; iCol < 5; iCol++)
        {
            bTemp = bTemp & marked[iRow][iCol];
        }

        if (bTemp)
        {
            return true;
        }
    }

    for (size_t iCol = 0; iCol < 5; iCol++)
    {
        bTemp = true;
        for (size_t iRow = 0; iRow < 5; iRow++)
        {
            bTemp = bTemp & marked[iRow][iCol];
        }

        if (bTemp)
        {
            return true;
        }
    }

    return false;
}

int Cardboard::getScore(int lastNumber)
{
    //cout << "getScore::Called with " << lastNumber << endl;
    int iScore = 0;

    for (size_t iRow = 0; iRow < 5; iRow++)
    {
        for (size_t iCol = 0; iCol < 5; iCol++)
        {
            //cout << "[" << iRow << "," << iCol << "] -> " << numbers[iRow][iCol] << " & " << marked[iRow][iCol] << endl;
            iScore += (marked[iRow][iCol] ? 0 : numbers[iRow][iCol]);
        }
    }

    return iScore * lastNumber;
}

void Cardboard::checkNumber(int number)
{
    for (size_t iRow = 0; iRow < 5; iRow++)
    {
        for (size_t iCol = 0; iCol < 5; iCol++)
        {
            //cout << "Compare " << number << " with position [" << iRow << "][" << iCol << "](" << numbers[iRow][iCol] << ")." << endl;
            if (numbers[iRow][iCol] == number)
            {
                cout << "Marked " << number << " in position [" << iRow << "][" << iCol << "]." << endl;
                marked[iRow][iCol] = true;
            }
        }
    }
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

short int siReadAndProcessInput(string sFileName, vector<int> &vNumbers, vector<Cardboard> &vCardboards)
{
    ifstream fInputFile;
    string sLine;
    bool bNewMark = false;
    size_t zPos = 0;
    Cardboard* vTemp  = new Cardboard();

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        /* Get 1st special line */
        if (getline(fInputFile, sLine))
        {
            while ((zPos = sLine.find(',')) != string::npos)
            {
                vNumbers.push_back(stoi(sLine.substr(0, zPos)));
                sLine.erase(0, zPos+1);
            }
        }
        else
        {
            fInputFile.close();
            return 1;
        }

        /* Empty line */
        getline(fInputFile,sLine);

        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
            {
                vCardboards.push_back(*vTemp);
                vTemp = new Cardboard();
                continue;
            }

            //cout << sLine << endl;
            ltrim(sLine);
            while ((zPos = sLine.find("  ")) != string::npos)
            {
                sLine.replace(zPos, 2, " ");
            }

            while ((zPos = sLine.find(' ')) != string::npos)
            {
                //cout << sLine << " ";
                vTemp->numbers[vTemp->iCurrentInputRow][vTemp->iCurrentInputCol] = stoi(sLine.substr(0, zPos));
                vTemp->marked[vTemp->iCurrentInputRow][vTemp->iCurrentInputCol] = false;
                sLine.erase(0, zPos+1);
                vTemp->iCurrentInputCol++;
            }
            vTemp->numbers[vTemp->iCurrentInputRow][vTemp->iCurrentInputCol] = stoi(sLine.substr(0, zPos));
            vTemp->marked[vTemp->iCurrentInputRow][vTemp->iCurrentInputCol] = false;

            //cout << endl;
            vTemp->iCurrentInputRow++;
            vTemp->iCurrentInputCol = 0;
        }

        if (vTemp->iCurrentInputRow != 0)
        {
            vCardboards.push_back(*vTemp);
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
    vector<int> vAppearedNumbers;
    vector<Cardboard> vCardboards;

    if (!siReadAndProcessInput("input.txt", vAppearedNumbers, vCardboards))
    {
        cout << "Read " << vCardboards.size() << " cards and " << vAppearedNumbers.size() << " numbers to check." << endl;
        cout << vCardboards[99].numbers[4][0] << endl;
        for (auto &&iNumber : vAppearedNumbers)
        {
            //cout << "Number is " << iNumber << endl;
            for (size_t iPos = 0; iPos < vCardboards.size(); iPos++)
            {
                vCardboards[iPos].checkNumber(iNumber);
                if (vCardboards[iPos].isWinner())
                {
                    cout << "Found the first winning card. Score -> " << vCardboards[iPos].getScore(iNumber) << endl;
                    return 0;
                }
            }
        }
    }
    else
    {
        return 1;
    }

    return 0;
}
