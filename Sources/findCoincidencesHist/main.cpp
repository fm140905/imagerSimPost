#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <utility>
#include <set>
#include <map>
#include <random>

#include "reader.h"

class NormalRandNumGenerator
{
private:
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
public:
    NormalRandNumGenerator(double mean, double stddev)
        : distribution(mean, stddev)
    {}
    NormalRandNumGenerator(double mean, double stddev, int seed)
        : generator(seed), distribution(mean, stddev) 
    {}
    double genRandNumber() {return distribution(generator);}
};

class UniformRandNumGenerator
{
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
public:
    UniformRandNumGenerator(double xmin, double xmax)
        : distribution(xmin, xmax)
    {}
    UniformRandNumGenerator(double xmin, double xmax, int seed)
        : generator(seed), distribution(xmin, xmax) 
    {}
    double genRandNumber() {return distribution(generator);}
};

class MyPulse
{
public:
    ulong histNo=0; // history number
    // double timeStamp=0; // time stamp, ns
    double Ein=0; // initial photon energy, MeV
    double height=0; // pulse amplitude, MeV
    int cellNo=0; // cell number
    Vector3D pos; // position, cm
    MyPulse() {}
    MyPulse(std::string record) {
        histNo = std::stoi(record.substr(54, 10));
        // timeStamp = std::stod(record.substr(14, 24));
        height = std::stod(record.substr(77, 9));
        // reaction = std::stoi(record.substr(88, 4));
        Ein = std::stod(record.substr(159, 11)); // photon energy before interaction
        cellNo = std::stoi(record.substr(137, 9));
        pos = Vector3D(std::stod(record.substr(177, 6)), 
                       std::stod(record.substr(185, 6)),
                       std::stod(record.substr(193, 6)));
    }
};

bool comparator(const MyPulse &a, const MyPulse &b);

bool processCoincidence(const std::vector<MyPulse>& pulses, Cone& newCone){
    if (pulses.size() != 2)
    {
        return false;
    }
    // if (std::abs(pulses[1].height + pulses[0].height - 0.662 ) > 0.05)
    // {
    //     return false;
    // }
    
    double cosHalfangle = 1 - pulses[0].height * 0.511 / (pulses[1].height * (pulses[1].height + pulses[0].height));
    if (std::abs(cosHalfangle)>=1)
    {
        return false;
    }
    Vector3D axis = pulses[1].pos - pulses[0].pos;
    if (axis * axis == 0){
        return false;
    }
    newCone = Cone(pulses[0].pos, axis, cosHalfangle, 
                   pulses[0].height + pulses[1].height, pulses[0].height);
    return true;
}

int main(int argc, char** argv)
{
    // NormalRandNumGenerator normalRandGen(0, 0.3 / 2.355);// FWHM = 3mm
    UniformRandNumGenerator uniformRandGen(0, 0.3);
    UniformRandNumGenerator uniformRandGen2(0, 0.5);
    const int maxN = 10000;
    std::string dir = argv[1];
    std::string pulseFile("/pulses_with_pos.txt");
    std::string outpath("/cones.txt");
    pulseFile = dir + pulseFile;
    outpath = dir + outpath;

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
    std::string line;
    std::vector<MyPulse> pulses;
    std::vector<Cone> cones;
    std::vector<ulong> histryNumbers;
    // const double timeWindow = 50; // dt = 10 ns
    // double prevTT(0);
    ulong prevHistNum(0);
    // std::getline(fpulse, line); // skip first line
    int counts = 0;
    while (std::getline(fpulse, line))
    {   
        MyPulse newPulse = MyPulse(line);
        if (newPulse.height < 0.05) // 50 keV energy threshold
            continue;
        
        newPulse.pos.X += uniformRandGen.genRandNumber();
        newPulse.pos.Y += uniformRandGen.genRandNumber();
        newPulse.pos.Z += uniformRandGen2.genRandNumber();

        if (pulses.size() > 0 && newPulse.histNo != prevHistNum)
        {
            // process pulses
            Cone newCone;
            // sort pulses by incoming photon energy
            std::sort(pulses.begin(), pulses.end(), comparator);
            if (processCoincidence(pulses, newCone))
            {
                histryNumbers.push_back(pulses[0].histNo);
                cones.push_back(std::move(newCone));
                counts++;
                if (counts > maxN)
                {
                    break;
                }
            }
            pulses.clear();
        }
        prevHistNum = newPulse.histNo;
        pulses.push_back(std::move(newPulse));
    }
    fpulse.close();

    // save cones to text file
    outfile << "  apex.x  apex.y  apex.z  axis.x  axis.y  axis.z  cosHalfAngle       E1+E2           E1   history_number\n";
    for (int i = 0; i < cones.size(); i++)
    {
        outfile << std::fixed << std::setprecision(2)
                << std::setw(8) << cones[i].apex.X // << "    "
                << std::setw(8) << cones[i].apex.Y // << "    "
                << std::setw(8) << cones[i].apex.Z // << "    "
                << std::setw(8) << cones[i].axis.X // << "    "
                << std::setw(8) << cones[i].axis.Y // << "    "
                << std::setw(8) << cones[i].axis.Z // << "    "
                << std::fixed << std::setprecision(8)
                << std::setw(13) << cones[i].cosHalfAngle
                << std::setw(13) << cones[i].E0
                << std::setw(13) << cones[i].Edpst
                << std::setw(13) << histryNumbers[i] << '\n';
    }
    outfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl; 
    return 0;
}

bool comparator(const MyPulse &a, const MyPulse &b)
{
    return a.Ein > b.Ein;
}