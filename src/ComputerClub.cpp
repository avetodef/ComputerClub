#include "ComputerClub.hpp"
#include "ProcessableEvent.hpp"
#include <iostream>
#include <algorithm>

void ComputerClub::manageEvents(EventVisitor& visitor, const std::vector<Event *>& incomingEvents){
    std::cout << "Starting to manage incoming events. Total events: " << incomingEvents.size() << std::endl;

    for (auto & event : incomingEvents){
        std::cout << "Processing event: " << event->toString() << std::endl;

        ProcessableEvent * processableEvent = static_cast<ProcessableEvent *>(event);
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

int ComputerClub::countRevenue(){
    std::cout << "Calculating total revenue from all tables..." << std::endl;

    int result = 0;
    for (auto & table : tables){
        int tableRevenue = table.getTotalRevenue();
        std::cout << "Revenue from table " << table.getId() << ": " << tableRevenue << std::endl;
        result += tableRevenue;
    }

    std::cout << "Total revenue calculated: " << result << std::endl;
    return result;
}