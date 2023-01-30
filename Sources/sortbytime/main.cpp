#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <utility>

#include "reader.h"

class MyPulse
{
public:
    ulong histNo=0; // history number
    double timeStamp=0; // time stamp, ns
    double height=0; // pulse amplitude, MeV
    int cellNo=0; // cell number
    Vector3D pos; // position, cm
    MyPulse() {}
    MyPulse(std::string record) {
        histNo = std::stoi(record.substr(54, 10));
        timeStamp = std::stod(record.substr(14, 24));
        height = std::stod(record.substr(77, 9));
        // reaction = std::stoi(record.substr(88, 4));
        cellNo = std::stoi(record.substr(137, 9));
        pos = Vector3D(std::stod(record.substr(177, 6)), 
                       std::stod(record.substr(185, 6)),
                       std::stod(record.substr(193, 6)));
    }
};

int main(int argc, char** argv)
{
    std::string dir = argv[1];
    std::string pulseFile("/pulses_with_pos.txt");
    std::string outpath("/pulses_with_pos_sort_by_time.txt");
    pulseFile = dir + pulseFile;
    outpath = dir + outpath;
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/Test/pulses_with_pos.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/Test/pulses_with_pos_sort_by_time.txt");

    std::ifstream fpulse;
    fpulse.open(pulseFile, std::ios::in);
    if (!fpulse.good())
    {
        throw std::invalid_argument("Cannot open pulse file");
    }

    std::ofstream outfile;
    outfile.open(outpath, std::ios::out);
    if (!outfile.good())
    {
        throw std::invalid_argument("Cannot create file: " + outpath);
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    // std::vector<std::pair<ulong, std::string>> pulses;
    std::vector<MyPulse> pulses;
    // pulses.reserve(16882479);
    std::string line;
    while (std::getline(fpulse, line))
    {
        pulses.push_back(MyPulse(line));
    }
    fpulse.close();

    std::sort(pulses.begin(), pulses.end(),
                [](const MyPulse & a, const MyPulse & b) -> bool
                { 
                    return a.timeStamp < b.timeStamp; 
                });

    outfile << "Timestamp(ns)           E_d(MeV)     x(cm)   y(cm)   z(cm)   Cell_number  History_number\n";
    for (int i = 0; i < pulses.size(); i++)
    {
        outfile << std::fixed << std::setprecision(8)
                << std::setw(24) << pulses[i].timeStamp
                << std::setw(13) << pulses[i].height
                << std::fixed << std::setprecision(2)
                << std::setw(8) << pulses[i].pos.X
                << std::setw(8) << pulses[i].pos.Y
                << std::setw(8) << pulses[i].pos.Z
                << std::setw(13) << pulses[i].cellNo
                << std::setw(13) << pulses[i].histNo << '\n';
    }
    outfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl; 
    return 0;
}