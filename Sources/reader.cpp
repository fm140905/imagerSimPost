#include "reader.h"

Vector3D getPos(const std::vector<Event>& events, const int& cellNo)
{
    // the interaction that deposits most energy in the target cell
    Vector3D pos;
    double maxDpstErg(0);
    for (int i = 0; i < events.size(); i++)
    {
        if (events[i].cellNo == cellNo && events[i].ergDpst > maxDpstErg)
        {
            maxDpstErg = events[i].ergDpst;
            pos = events[i].pos;
        }
    }
    return pos;
    
}