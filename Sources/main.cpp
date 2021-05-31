#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <set>

#include "reader.h"

int main(int argc, char** argv)
{
    ulong maxN = 100000;
    std::string dumnFile("/media/ming/DATA/projects/imager/Postprocessing/polimi/dumn1");
    std::string pulseFile("/media/ming/DATA/projects/imager/Postprocessing/polimi/imager_All_pulses.o");
    std::string outpath("/media/ming/DATA/projects/imager/Postprocessing/polimi/cones.txt");
    // test run
    // std::string dumnFile("/media/ming/DATA/projects/imager/Postprocessing/Test/collision.txt");
    // std::string pulseFile("/media/ming/DATA/projects/imager/Postprocessing/Test/pulses.txt");
    // std::string outpath("/media/ming/DATA/projects/imager/Postprocessing/Test/cones.txt");
    std::set<int> channels = {13, 15, 17, 19, 21,
                              53, 55, 57, 59, 61,
                              73, 75, 77, 79, 81,
                              93, 95, 97, 99, 101,
                              303, 305, 307, 309, 311,
                              503, 505, 507, 509, 511};

    std::ifstream fdumn;
    fdumn.open(dumnFile, std::ios::in);
    if (!fdumn.good())
    {
        throw std::invalid_argument("Cannot open collision file");
    }
    
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
    // reconstruct events
    std::vector<Cone> cones;
    std::vector<ulong> histryNumbers;
    double cosHalfangle;
    Vector3D apex;
    Vector3D axis;
    std::string pulseLine;
    std::string dumnLine;
    std::string prevDumnLine("");
    std::vector<Pulse> pulses; // pulses with same history number
    u_long histNo(0); 
    while (std::getline(fpulse, pulseLine))
    {
        // parse line
        Pulse newPulse(pulseLine);
        // if line.histNo == histNo, add this pulse, go to next line
        if (newPulse.histNo == histNo || histNo == 0 || pulses.size() == 0)
        {
            // // pick up channels of interest
            if (channels.find(newPulse.cellNo) != channels.end())
            {
                // update histNo; 
                histNo = newPulse.histNo;
                pulses.push_back(std::move(newPulse));
                continue;
            }
            
        }
        // else, process vector of pulses; 
        // if (pulses.size() > 1)
        if (pulses.size() == 2)
        {
            // sort the pulses based on incoming photon energy
            std::sort(pulses.begin(), pulses.end(),
                    [](const Pulse & a, const Pulse & b) -> bool
                    { 
                        return a.ergIn > b.ergIn; 
                    });
            // remove anomalies
            // if (std::abs(pulses[0].ergIn - 0.661) < 0.001 && pulses[0].height < pulses[0].ergIn)
            {
                // compute scattering angle
                // cosHalfangle = 1 - pulses[0].height * 0.511 / (pulses[0].ergIn * (pulses[0].ergIn - pulses[0].height));
                cosHalfangle = 1 - pulses[0].height * 0.511 / (pulses[1].height * (pulses[1].height + pulses[0].height));
                if (std::abs(cosHalfangle) < 1)
                {
                    // discard cost >= 1, i.e., multiple compton scattering 
                    // get position from collision file
                    std::vector<Event> interactions;
                    if (prevDumnLine.length() > 0)
                    {
                        u_long histNotmp = stoi(prevDumnLine.substr(0, 10));
                        if (histNotmp == histNo)
                        {
                            interactions.push_back(Event(prevDumnLine));
                        }
                    }
                    
                    while (std::getline(fdumn, dumnLine))
                    {
                        u_long histNotmp = stoi(dumnLine.substr(0, 10));
                        if (histNotmp < histNo)
                            continue;                    
                        else if (histNotmp > histNo)
                        {
                            // overshoot
                            prevDumnLine = dumnLine;
                            // process vector interactions
                            // find the interaction that deposits most energy in given cell
                            // apex = site 1
                            // axis = site 2 -site 1
                            apex = getPos(interactions, pulses[0].cellNo);
                            axis =  getPos(interactions, pulses[1].cellNo) - apex;
                            break;
                        }
                        else
                        {
                            interactions.push_back(Event(dumnLine));
                        }
                    }
                    if (fdumn.eof())
                    {
                        break;
                    }
                    if (axis * axis > 0)
                    {
                        // axis could be a zero vector if interactions occur at the edge
                        // cones.push_back(Cone(apex, axis, cosHalfangle, pulses[0].ergIn, pulses[0].height));
                        cones.push_back(Cone(apex, axis, cosHalfangle, pulses[0].height + pulses[1].height, pulses[0].height));
                        histryNumbers.push_back(histNo);
                    }
                    if (cones.size() > maxN)
                    {
                        break;
                    }
                } 
            }
        }
        // empty vector pulses;
        pulses.clear(); 
        // update histNo; 
        histNo = newPulse.histNo;
        // add current line to vector;
        pulses.push_back(Pulse(std::move(newPulse))); 
        //go to next line
    }
    
    fdumn.close();
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