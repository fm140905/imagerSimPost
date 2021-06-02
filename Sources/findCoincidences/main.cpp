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
        timeStamp = std::stod(record.substr(0, 24));
        height = std::stod(record.substr(27, 10));
        pos = Vector3D(std::stod(record.substr(39, 6)), 
                       std::stod(record.substr(47, 6)),
                       std::stod(record.substr(55, 6)));
        cellNo = std::stoi(record.substr(68, 6));
        histNo = std::stoi(record.substr(77, 10));
    }
};

bool processCoincidence(const std::vector<MyPulse>& pulses, Cone& newCone){
    if (pulses.size() != 2)
    {
        return false;
    }
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
    const int maxN = 10000;
    std::string pulseFile("/media/ming/DATA/projects/Postprocessing/simulation_2/pulses_with_pos_sort_by_time.txt");
    std::string outpath("/media/ming/DATA/projects/Postprocessing/simulation_2/cones.txt");
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/Test/pulses_with_pos_sort_by_time.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/Test/cones.txt");
    std::map<int, Vector3D> pixelPos{{13, {0.4,1.505,0}}, {15, {0.4,2.365,0}}, {17, {0.4, 3.225, 0}}, {19, {0.4, 4.085, 0}},{21, {0.4, 4.945, 0}},
                                     {53, {2.0,1.505,0}}, {55, {2.0,2.365,0}}, {57, {2.0, 3.225, 0}}, {59, {2.0, 4.085, 0}},{61, {2.0, 4.945, 0}},
                                     {93, {3.6,1.505,0}}, {95, {3.6,2.365,0}}, {97, {3.6, 3.225, 0}}, {99, {3.6, 4.085, 0}},{101, {3.6, 4.945, 0}},
                                     {303, {5.2,1.505,0}}, {305, {5.2,2.365,0}}, {307, {5.2, 3.225, 0}}, {309, {5.2, 4.085, 0}},{311, {5.2, 4.945, 0}},
                                     {503, {6.8,1.505,0}}, {505, {6.8,2.365,0}}, {507, {6.8, 3.225, 0}}, {509, {6.8, 4.085, 0}},{511, {6.8, 4.945, 0}}};
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
    const double timeWindow = 50; // dt = 10 ns
    double prevTT(0);
    std::getline(fpulse, line); // skip first line
    int counts = 0;
    while (std::getline(fpulse, line))
    {   
        MyPulse newPulse = MyPulse(line);
        auto search = pixelPos.find(newPulse.cellNo);
        if (search == pixelPos.end()){
            continue;
        }
        else {
            newPulse.pos.X = search->second.X;
            newPulse.pos.Y = search->second.Y;
        }
        if (pulses.size() == 0 || std::abs(newPulse.timeStamp - prevTT) < timeWindow)
        {
            prevTT = newPulse.timeStamp;
            pulses.push_back(std::move(newPulse));
        }
        else if (std::abs(newPulse.timeStamp - prevTT) >= timeWindow)
        {
            // process pulses
            Cone newCone;
            if (processCoincidence(pulses, newCone))
            {
                histryNumbers.push_back(pulses[0].histNo);
                cones.push_back(std::move(newCone));
                // counts++;
                // if (counts > maxN)
                // {
                //     break;
                // }
            }
            pulses.clear();
            prevTT = newPulse.timeStamp;
            pulses.push_back(std::move(newPulse));
        }
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