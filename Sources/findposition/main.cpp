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
    // std::string dumnFile("/media/ming/DATA/projects/Postprocessing/simulation_2/dumn1");
    // std::string pulseFile("/media/ming/DATA/projects/Postprocessing/simulation_2/pulses_sort_by_hist.txt");
    // std::string outpath("/media/ming/DATA/projects/Postprocessing/simulation_2/pulses_with_pos.txt");
    // test run
    std::string dumnFile("/media/ming/DATA/projects/Postprocessing/Test/collision.txt");
    std::string pulseFile("/media/ming/DATA/projects/Postprocessing/Test/pulses_sort_by_hist.txt");
    std::string outpath("/media/ming/DATA/projects/Postprocessing/Test/pulses_with_pos.txt");
    // std::set<int> channels = {13, 15, 17, 19, 21,
    //                           53, 55, 57, 59, 61,
    //                           73, 75, 77, 79, 81,
    //                           93, 95, 97, 99, 101,
    //                           303, 305, 307, 309, 311,
    //                           503, 505, 507, 509, 511};

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
    std::string pulseLine;
    std::string dumnLine;
    std::string prevDumnLine("");
    // pulses with same history number
    std::vector<std::pair<Pulse, std::string>> pulses;
    u_long histNo(0); 
    int counts(0);
    while (std::getline(fpulse, pulseLine))
    {
        pulseLine.pop_back();
        // parse line
        Pulse newPulse(pulseLine);
        // if line.histNo == histNo, add this pulse, go to next line
        if (newPulse.histNo == histNo || histNo == 0 || pulses.size() == 0)
        {
                // update histNo; 
                histNo = newPulse.histNo;
                pulses.push_back(std::make_pair(std::move(newPulse), pulseLine));
                counts++;
                continue;  
        }
        // else, process vector of pulses; 
        // sort the pulses based on time stamp
        std::sort(pulses.begin(), pulses.end(),
                [](const std::pair<Pulse, std::string> & a, const std::pair<Pulse, std::string> & b) -> bool
                { 
                    return a.first.timeStamp < b.first.timeStamp; 
                });
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
                for (int i = 0; i < pulses.size(); i++)
                {
                    Vector3D pos = getPos(interactions, pulses[i].first.cellNo);
                    outfile << pulses[i].second << "    "
                            << std::fixed << std::setprecision(2)
                            << std::setw(8) << pos.X // << "    "
                            << std::setw(8) << pos.Y // << "    "
                            << std::setw(8) << pos.Z << '\n';
                }
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
        // empty vector pulses;
        pulses.clear(); 
        // update histNo; 
        histNo = newPulse.histNo;
        // add current line to vector;
        pulses.push_back(std::make_pair(std::move(newPulse), pulseLine));
        //go to next line
        counts++;
        if (counts > maxN)
        {
            break;
        }
    }
    
    fdumn.close();
    fpulse.close();
    outfile.close();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl; 
    return 0;
}