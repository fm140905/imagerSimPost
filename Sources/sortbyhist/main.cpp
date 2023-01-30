#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <utility>


int main(int argc, char** argv)
{
    std::string dir = argv[1];
    std::string pulseFile("/imager_All_pulses.o");
    std::string outpath("/pulses_sort_by_hist.txt");
    pulseFile = dir + pulseFile;
    outpath = dir + outpath;
    // std::cout << pulseFile << std::endl;
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/Test/pulses.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/Test/pulses_sort_by_hist.txt");

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
    std::vector<std::pair<ulong, std::string>> pulses;
    // pulses.reserve(16882479);
    std::string line;
    while (std::getline(fpulse, line))
    {
        pulses.push_back(std::make_pair(std::stoi(line.substr(54, 10)), line));
    }
    fpulse.close();

    std::sort(pulses.begin(), pulses.end());

    for (int i = 0; i < pulses.size(); i++)
    {
        outfile << pulses[i].second << '\n';
    }
    outfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl; 
    return 0;
}