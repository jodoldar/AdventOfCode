/**
 * @file part2.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 8 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

class Segment
{
public:
    char h_up, h_mid, h_down;
    char v_up_lft, v_up_rgh;
    char v_dw_lft, v_dw_rgh;

    Segment(){
        h_up = h_mid = h_down = v_up_lft = v_up_rgh = v_dw_lft = v_dw_rgh = 0;
    };

    string generateStatus();
    friend ostream& operator<<(ostream& os, const Segment& obj);
    int seg2int(string code);
    string decode(string code);
    string seg2fancy(int number);
};

string Segment::generateStatus()
{
    string sReturn = "";

    if (h_up != 0)
        sReturn.push_back(h_up);
    if (h_mid != 0)
        sReturn.push_back(h_mid);
    if (h_down != 0)
        sReturn.push_back(h_down);
    if (v_up_lft != 0)
        sReturn.push_back(v_up_lft);
    if (v_up_rgh != 0)
        sReturn.push_back(v_up_rgh);
    if (v_dw_lft != 0)
        sReturn.push_back(v_dw_lft);
    if (v_dw_rgh != 0)
        sReturn.push_back(v_dw_rgh);

    sort(sReturn.begin(), sReturn.end());

    return sReturn;
}

ostream& operator<<(ostream& os, const Segment& obj)
{
    os << "h_up->" << obj.h_up << " ";
    os << "h_mid->" << obj.h_mid << " ";
    os << "h_down->" << obj.h_down << " ";
    os << "v_up_lft->" << obj.v_up_lft << " ";
    os << "v_up_rgh->" << obj.v_up_rgh << " ";
    os << "v_dw_lft->" << obj.v_dw_lft << " ";
    os << "v_dw_rgh->" << obj.v_dw_rgh << " ";

    return os;
}

string Segment::decode(string code)
{
    string sRet = "";

    for (auto &&letter : code)
    {
        if (letter == h_up) {
            sRet.push_back('A');
        } else if (letter == h_mid) {
            sRet.push_back('D');
        } else if (letter == h_down) {
            sRet.push_back('G');
        } else if (letter == v_up_lft) {
            sRet.push_back('B');
        } else if (letter == v_up_rgh) {
            sRet.push_back('C');
        } else if (letter == v_dw_lft) {
            sRet.push_back('E');
        } else if (letter == v_dw_rgh) {
            sRet.push_back('F');
        }
    }

    sort(sRet.begin(), sRet.end());

    return sRet;
}

int Segment::seg2int(string code)
{
    string decoded = decode(code);

    if (decoded.compare("ABCEFG") == 0) {
        return 0;
    } else if (decoded.compare("CF") == 0) {
        return 1;
    } else if (decoded.compare("ACDEG") == 0) {
        return 2;
    } else if (decoded.compare("ACDFG") == 0) {
        return 3;
    } else if (decoded.compare("BCDF") == 0) {
        return 4;
    } else if (decoded.compare("ABDFG") == 0) {
        return 5;
    } else if (decoded.compare("ABDEFG") == 0) {
        return 6;
    } else if (decoded.compare("ACF") == 0) {
        return 7;
    } else if (decoded.compare("ABCDEFG") == 0) {
        return 8;
    } else if (decoded.compare("ABCDFG") == 0) {
        return 9;
    }

    return -1;
}

string Segment::seg2fancy(int number)
{
    /* First line */
    int i1, i2, i3, i4;
    i4 = number % 10;
    number /= 10;
    i3 = number % 10;
    number /= 10;
    i2 = number % 10;
    number /= 10;
    i1 = number % 10;

    string sLine1 = "", sLine2 = "", sLine3 = "";
    (i1 == 1 || i1 == 4) ? sLine1.append("   ") : sLine1.append(" _ ");
    (i2 == 1 || i2 == 4) ? sLine1.append("   ") : sLine1.append(" _ ");
    (i3 == 1 || i3 == 4) ? sLine1.append("   ") : sLine1.append(" _ ");
    (i4 == 1 || i4 == 4) ? sLine1.append("   ") : sLine1.append(" _ ");

    if (i1 == 1 || i1 == 2 || i1 == 3 || i1 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }
    if (i1 == 0 || i1 == 1 || i1 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("_");
    }
    if (i1 == 5 || i1 == 6 ) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }

    if (i2 == 1 || i2 == 2 || i2 == 3 || i2 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }
    if (i2 == 0 || i2 == 1 || i2 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("_");
    }
    if (i2 == 5 || i2 == 6 ) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }

    if (i3 == 1 || i3 == 2 || i3 == 3 || i3 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }
    if (i3 == 0 || i3 == 1 || i3 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("_");
    }
    if (i3 == 5 || i3 == 6 ) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }

    if (i4 == 1 || i4 == 2 || i4 == 3 || i4 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }
    if (i4 == 0 || i4 == 1 || i4 == 7) {
        sLine2.append(" ");
    } else {
        sLine2.append("_");
    }
    if (i4 == 5 || i4 == 6 ) {
        sLine2.append(" ");
    } else {
        sLine2.append("|");
    }


    if (i1 == 0 || i1 == 2 || i1 == 6 || i1 == 8) {
        sLine3.append("|");
    } else {
        sLine3.append(" ");
    }
    if (i1 == 1 || i1 == 4 || i1 == 7) {
        sLine3.append(" ");
    } else {
        sLine3.append("_");
    }
    if (i1 == 2 ) {
        sLine3.append(" ");
    } else {
        sLine3.append("|");
    }

    if (i2 == 0 || i2 == 2 || i2 == 6 || i2 == 8) {
        sLine3.append("|");
    } else {
        sLine3.append(" ");
    }
    if (i2 == 1 || i2 == 4 || i2 == 7) {
        sLine3.append(" ");
    } else {
        sLine3.append("_");
    }
    if (i2 == 2 ) {
        sLine3.append(" ");
    } else {
        sLine3.append("|");
    }

    if (i3 == 0 || i3 == 2 || i3 == 6 || i3 == 8) {
        sLine3.append("|");
    } else {
        sLine3.append(" ");
    }
    if (i3 == 1 || i3 == 4 || i3 == 7) {
        sLine3.append(" ");
    } else {
        sLine3.append("_");
    }
    if (i3 == 2 ) {
        sLine3.append(" ");
    } else {
        sLine3.append("|");
    }

    if (i4 == 0 || i4 == 2 || i4 == 6 || i4 == 8) {
        sLine3.append("|");
    } else {
        sLine3.append(" ");
    }
    if (i4 == 1 || i4 == 4 || i4 == 7) {
        sLine3.append(" ");
    } else {
        sLine3.append("_");
    }
    if (i4 == 2 ) {
        sLine3.append(" ");
    } else {
        sLine3.append("|");
    }

    return sLine1 + "\n" + sLine2 + "\n" + sLine3;
}

short int siReadAndProcessInput(string sFileName, vector<Segment> &vNumbers, vector<vector<string>> &vMessages)
{
    ifstream fInputFile;
    string sLine, sCodedNumbers, sMessage;
    size_t zPos;
    string s1,s4,s7,s8;
    vector<string> vsAlphabet;
    vector<string> vsMessage;
    Segment *oSegment;
    string sortedWord, sorted8;
    vector<char> grammar = {'a','b','c','d','e','f','g'};

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            zPos = sLine.find('|');

            sCodedNumbers = sLine.substr(0,zPos);
            trim(sCodedNumbers);

            sMessage = sLine.erase(0, zPos+1);
            trim(sMessage);

            /* Decode alphabet */
            vsAlphabet.clear();
            vsMessage.clear();
            oSegment = new Segment();

            while ((zPos = sCodedNumbers.find(' ')) != string::npos)
            {
                vsAlphabet.push_back(sCodedNumbers.substr(0, zPos));
                sCodedNumbers.erase(0, zPos+1);
            }
            vsAlphabet.push_back(sCodedNumbers);

            while ((zPos = sMessage.find(' ')) != string::npos)
            {
                vsMessage.push_back(sMessage.substr(0, zPos));
                sMessage.erase(0, zPos+1);
            }
            vsMessage.push_back(sMessage);

            /* Step 1 - Extract 1,4,7,8 */
            s1 = *find_if(vsAlphabet.begin(), vsAlphabet.end(), [](string elem){return elem.length()==2;});
            s4 = *find_if(vsAlphabet.begin(), vsAlphabet.end(), [](string elem){return elem.length()==4;});
            s7 = *find_if(vsAlphabet.begin(), vsAlphabet.end(), [](string elem){return elem.length()==3;});
            s8 = *find_if(vsAlphabet.begin(), vsAlphabet.end(), [](string elem){return elem.length()==7;});
            //cout << "Step 1 -> " << s1 << " " << s4 << " " << s7 << " " << s8 << endl;

            /* Step 2 - Extract h_up */
            for (auto &&letter : s7)
            {
                size_t zPos = s1.find(letter);
                //cout << letter << " " << zPos << endl;
                if (zPos==string::npos)
                {
                    //cout << "Letter " << letter << " not found in " << s1 << endl;
                    oSegment->h_up = letter;
                    break;
                }
            }
            //cout << "Step 2 -> " << *oSegment << endl;

            /* Step 3 - Extract 6 */
            vector<string> sixers;

            for (auto &&word : vsAlphabet)
            {
                if (word.length() == 6)
                {
                    if (word.find(s1[0])==string::npos)
                    {
                        oSegment->v_up_rgh = s1[0];
                        oSegment->v_dw_rgh = s1[1];

                        sixers.push_back(word);

                        break;
                    }
                    else if (word.find(s1[1])==string::npos)
                    {
                        oSegment->v_up_rgh = s1[1];
                        oSegment->v_dw_rgh = s1[0];

                        sixers.push_back(word);

                        break;
                    }
                }
            }
            //cout << "Step 3 -> " << *oSegment << endl;

            /* Step 4 - Extract 0 */
            string red4 = "";
            for (auto &&letter : s4)
            {
                if (s1.find(letter)==string::npos)
                {
                    red4.push_back(letter);
                }
            }

            for (auto &&word : vsAlphabet)
            {
                if (word.length() == 6)
                {
                    if (word.find(red4[0])==string::npos)
                    {
                        oSegment->h_mid = red4[0];
                        oSegment->v_up_lft = red4[1];

                        sixers.push_back(word);

                        break;
                    }
                    else if (word.find(red4[1])==string::npos)
                    {
                        oSegment->h_mid = red4[1];
                        oSegment->v_up_lft = red4[0];

                        sixers.push_back(word);

                        break;
                    }
                }
            }
            //cout << "Step 4 -> " << *oSegment << endl;

            /* Step 5 - Extract 9 */
            for (auto &&word : vsAlphabet)
            {
                if (word.length() == 6 && (find(sixers.begin(), sixers.end(), word)==sixers.end()))
                {
                    for (auto &&letter : grammar)
                    {
                        if (word.find(letter)==string::npos)
                        {
                            oSegment->v_dw_lft = letter;
                            break;
                        }
                    }
                }
            }
            //cout << "Step 5 -> " << *oSegment << endl;

            /* Step 6 - Last segment */
            string current = oSegment->generateStatus();
            for (auto &&letter : grammar)
            {
                if(current.find(letter)==string::npos)
                {
                    oSegment->h_down = letter;
                    break;
                }
            }
            //cout << "Step 6 -> " << *oSegment << endl;

            vNumbers.push_back(*oSegment);
            vMessages.push_back(vsMessage);
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
    vector<Segment> vCodexes;
    vector<vector<string>> vMessages;
    int iAccount = 0;

    if (!siReadAndProcessInput("input.txt", vCodexes, vMessages))
    {
        for (size_t iPos = 0; iPos < vCodexes.size(); iPos++)
        {
            //cout << vCodexes[iPos] << endl;
            int iNum = 0;
            for (size_t iMsg = 0; iMsg < vMessages[iPos].size(); iMsg++)
            {
                //cout << vMessages[iPos][iMsg] << " " << vCodexes[iPos].decode(vMessages[iPos][iMsg]) << " ";
                //cout << vCodexes[iPos].seg2int(vMessages[iPos][iMsg]) << " ";

                iNum *= 10;
                iNum += vCodexes[iPos].seg2int(vMessages[iPos][iMsg]);
                //cout << iNum << " ";
            }

            cout << endl;
            cout << vCodexes[iPos].seg2fancy(iNum) << endl;

            iAccount += iNum;
            //cout << endl;
        }

        cout << "Final account is " << iAccount << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
