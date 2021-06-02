#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <utility>
#include <set>

#include "reader.h"

class MyPulse
{
public:
    ulong histNo=0; // history number
    double ergIn=0; // initial energy
    double height=0; // pulse amplitude, MeV
    int cellNo=0; // cell number
    Vector3D pos; // position, cm
    MyPulse() {}
    MyPulse(std::string record) {
        histNo = std::stoi(record.substr(54, 10));
        height = std::stod(record.substr(77, 9));
        // reaction = std::stoi(record.substr(88, 4));
        cellNo = std::stoi(record.substr(137, 9));
        ergIn = std::stod(record.substr(161, 10));
        pos = Vector3D(std::stod(record.substr(177, 6)), 
                       std::stod(record.substr(185, 6)),
                       std::stod(record.substr(193, 6)));
    }
};

bool processCoincidence(std::vector<MyPulse>& pulses, Cone& newCone){
    if (pulses.size() < 2)
    {
        return false;
    }
    std::sort(pulses.begin(), pulses.end(),
            [](const MyPulse & a, const MyPulse & b) -> bool
            { 
                return a.ergIn > b.ergIn; 
            });
    if (std::abs(pulses[0].ergIn - 0.661) > 0.05)
    {
        return false;
    }
    
    double cosHalfangle = 1 - pulses[0].height * 0.511 / (pulses[0].ergIn * (pulses[0].ergIn - pulses[0].height));
    if (std::abs(cosHalfangle)>=1)
    {
        return false;
    }
    Vector3D axis = pulses[1].pos - pulses[0].pos;
    if (axis * axis == 0){
        return false;
    }
    newCone = Cone(pulses[0].pos, axis, cosHalfangle, 
                   pulses[0].ergIn, pulses[0].height);
    return true;
}

int main(int argc, char** argv)
{
    const int maxN = 10000;
    std::string pulseFile("/media/ming/DATA/projects/Postprocessing/simulation_2/pulses_with_pos.txt");
    std::string outpath("/media/ming/DATA/projects/Postprocessing/simulation_2/cones_ideal.txt");
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/simulation_1/pulses_with_pos.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/simulation_1/cones_ideal.txt");
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/Test/pulses_with_pos.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/Test/cones_ideal.txt");

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
    int lino = 0;
    ulong histNo=0; // current history
    while (std::getline(fpulse, line))
    {
        // lino++;
        // if (lino > maxN)
        // {
        //     break;
        // }
        
        MyPulse newPulse = MyPulse(line);
        if (pulses.size() != 0 && newPulse.histNo != histNo)
        {
            // process pulses
            Cone newCone;
            if (processCoincidence(pulses, newCone))
            {
                histryNumbers.push_back(pulses[0].histNo);
                cones.push_back(std::move(newCone));
                if (cones.size() > maxN)
                {
                    break;
                }
            }
            pulses.clear();
        }
        histNo = newPulse.histNo;
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