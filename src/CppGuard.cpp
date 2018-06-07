//============================================================================
// Name        : CppGuard.cpp
// Author      : Akash Ravi
// Version     :
// Copyright   : www.akashravi.tk
// Description : Native C++ Code obfuscator
//============================================================================
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

const std::string TEMP_FILE = ".cppguard-temp-file.tmp";

bool containsOnlyWhite(const std::string &line)
{
    std::string temp = line;
    temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
    return temp.size() <= 0;
}

void stripLeadingWhite(std::string &line)
{
    if (line.size() > 0)
    {
        int nonWhiteIndex = 0;
        for (int i = 0; i < line.size(); ++i)
        {

            if (isspace(line.at(i)))
            {
                ++nonWhiteIndex;
            }
            else
            {
                break;
            }
        }

        line.erase(0, nonWhiteIndex);
    }
}

void stripSingleLineComment(std::string &line)
{
    if (line.size() >= 2)
    {
        int loc = line.find("//");
        if (loc != std::string::npos)
        {
            line.erase(loc);
        }
    }
}

void stripMultiLineComment(char *inFile)
{
    std::ifstream inFileStream(inFile);
    std::ofstream outFileStream(TEMP_FILE.c_str());
    std::string line;
    int startPos;
    int endPos;
    bool multiLine = false;
    while (std::getline(inFileStream, line))
    {

        if (!multiLine)
        {
            startPos = line.find("/*");
            if (startPos != std::string::npos)
            {
                endPos = line.find("*/");
                if (endPos != std::string::npos)
                {
                    int commentLength = (endPos + 2) - startPos;
                    line.erase(startPos, commentLength);
                    multiLine = false;
                }
                else
                {
                    multiLine = true;
                    line.erase();
                }
            }
        }
        else
        {

            endPos = line.find("*/");
            if (endPos != std::string::npos)
            {
                line.erase(0, endPos + 2);
                multiLine = false;
            }

            else
            {
                line.erase();
                multiLine = true;
            }
        }
        if (line.size() > 0)
        {
            outFileStream << line << std::endl;
        }
    }
    inFileStream.close();
    outFileStream.close();
}

std::string asciiReplace(std::string s)
{
    std::string p = "";
    int q;
    for (int i = 0; i <= s.size(); i++)
    {
        p += ('\\');
        p += ('x');
        std::stringstream stream;
        stream << std::hex << (int)s[i];
        std::string result(stream.str());
        p += result;
    }
    return p;
}

void obfuscateString(char *inFile)
{
    std::ifstream inFileStream(inFile);
    std::ofstream outFileStream(TEMP_FILE.c_str());
    std::string line;
    int startPos;
    int endPos;
    bool multiLine = false;
    while (std::getline(inFileStream, line))
    {

        if (!multiLine)
        {
            startPos = line.find("\"\"");
            if (startPos != std::string::npos)
            {
                endPos = line.find("\"\"");
                if (endPos != std::string::npos)
                {
                    int commentLength = (endPos + 2) - startPos;
                    line.erase(startPos, commentLength);
                    multiLine = false;
                }
                else
                {
                    multiLine = true;
                    line.erase();
                }
            }
        }
        else
        {

            endPos = line.find("\"\"");
            if (endPos != std::string::npos)
            {
                line.erase(0, endPos + 2);
                multiLine = false;
            }

            else
            {
                line.erase();
                multiLine = true;
            }
        }
        if (line.size() > 0)
        {
            outFileStream << line << std::endl;
        }
    }
    inFileStream.close();
    outFileStream.close();
}

int main(int argc, char *argv[])
{
    //std::string kk = "Akash";
    if (argc != 3)
    {
        //std::cerr << "\n\t" << asciiReplace(kk) << "\n\n";
        std::cerr << "\n\tWelcome to CppGuard - a cross platform C++ code obfuscator\n\n";
        std::cerr << "\t\tCurrently, this application is a command line utility\n";
        std::cerr << "\t\tUsage: ./cppguard infile outfile\n";
        exit(1);
    }

    std::string junkText = "int ppp = 23;string dds = std::bitset<63>(ppp).to_string();string hhh; string ggg;ggg = dds;ffrr(i, dds.size() - 2, dds.size()) hhh += dds[i];int hyy = hhh.size();dds.clear();ffrr(i, 0, 31 - hyy){dds += '1';}vvvsort(dds);vvvuni(dds);ffrr(i, 0, hyy){dds += hhh[i];}hyy = std::bitset<63>(ggg).to_ulong();ggg.clear();if(ggg.size()!=0)cout<<\"yedhukku\";reverse(dds.begin(),dds.end());";

    stripMultiLineComment(argv[1]);

    int jflag = 10;
    int fl = 0;

    std::ifstream inFileStream(TEMP_FILE.c_str());
    std::ofstream outFileStream(argv[2]);
    std::string line;
    outFileStream << "#include<bits/stdc++.h>" << std::endl;
    outFileStream << "#define ffrr(i,a,b) for(long long int i=a;i<b;i++)" << std::endl;
    outFileStream << "#define vvvsort(v) sort(v.begin(),v.end())" << std::endl;
    outFileStream << "#define vvvuni(vec) vec.erase( unique( vec.begin(), vec.end() ), vec.end() )" << std::endl;
    while (std::getline(inFileStream, line))
    {
        if (!containsOnlyWhite(line))
        {
            stripLeadingWhite(line);
            stripSingleLineComment(line);

            if (line.size() > 0)
            {
                if ((line.find("main(") != std::string::npos) and fl == 0)
                {

                    fl = 1;
                }
                if (fl == 1 and (line.find("{") != std::string::npos))
                {
                    jflag = 0;
                }
                if ((line.find("#include") != std::string::npos) or (line.find("# include") != std::string::npos))
                {
                    continue;
                }
                else if (line.find("#") != std::string::npos ||
                         line.find("using") != std::string::npos ||
                         line == "else")
                {

                    outFileStream << std::endl
                                  << line << std::endl;
                }
                else if (jflag == 0)
                {
                    outFileStream << std::endl
                                  << line << std::endl
                                  << junkText << std::endl;
                    jflag = 1;
                }
                else
                {
                    outFileStream << line;
                }
            }
        }
    }
    if (jflag == 1)
    {
    }
    inFileStream.close();
    outFileStream.close();
    remove(TEMP_FILE.c_str());
    return 0;
}
