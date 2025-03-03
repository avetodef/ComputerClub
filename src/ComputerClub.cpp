#include "ComputerClub.hpp"
#include "ProcessableEvent.hpp"
#include <algorithm>

void ComputerClub::manageEvents(EventVisitor& visitor, const std::vector<Event *>& incomingEvents){
    for (auto & event : incomingEvents){
        ProcessableEvent * processableEvent = dynamic_cast<ProcessableEvent *>(event);
        processableEvent->process(visitor);
    }

    std::sort(clientsInClub.begin(), clientsInClub.end(), [](const std::string& a, const std::string& b) {
        return a < b; //sort alphabetically
    });

    for (const std::string& client : clientsInClub){
        visitor.allEvents.push_back(visitor.getFactory().createEvent(closingTime, 11, client));

        auto tableIt = std::find_if(tables.begin(), tables.end(), [client](const Table & table) { return table.getClientName() == client; });
        if (tableIt != tables.end()){
            tableIt->countRevenue(tableIt->getOccupiedFrom(), closingTime, costPerHour);
            tableIt->updateTotalTimeOccupied(closingTime);
            tableIt->freeTable();
        }
    }
}