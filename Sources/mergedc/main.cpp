/*
 * @Description: 
 * @Author: Ming Fang
 * @Date: 2022-07-13 16:48:33
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-07-13 18:30:41
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
int main(int argc, char** argv)
{
    std::string dir = argv[1];
    // std::string dir = "/media/ming/DATA/projects/Postprocessing/07132022_largerNPS/oneSrc";
    std::string dumnFile("/comptonImager.dco");
    std::string outpath("/comptonImager.dc");
    dumnFile = dir + dumnFile;
    outpath = dir + outpath;

    std::ifstream fdumn;
    fdumn.open(dumnFile, std::ios::in);
    if (!fdumn.good())
    {
        throw std::invalid_argument("Cannot open collision file");
    }
    
    std::ofstream outfile;
    outfile.open(outpath, std::ios::out);
    if (!outfile.good())
    {
        throw std::invalid_argument("Cannot create file: " + outpath);
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    std::string dumnLine;
    std::string newLine;
    int64_t newHistNo(0);
    int64_t prevHistoNo(0);
    int64_t currHistNo(0);
    int subRunNo(0);
 
    while(std::getline(fdumn, dumnLine))
    {
        // select only gammas
        if(stoi(dumnLine.substr(19, 4)) != 2)
            continue;
        int64_t currHistNo = stoi(dumnLine.substr(0, 10));
        if (currHistNo < prevHistoNo)
        {
            subRunNo += 1;
        }
        if (subRunNo == 0)
        {
            outfile << dumnLine << '\n';
        }
        else
        {
            newHistNo = currHistNo + subRunNo * 200000000;
            outfile << std::setw(10) << newHistNo << dumnLine.substr(10) << '\n';
        }
        prevHistoNo = currHistNo;
    }
    outfile.close();
    fdumn.close();
    return 0;
}