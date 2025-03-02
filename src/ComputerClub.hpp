#include "EventVisitor.hpp"
#include "Time.hpp"
#include "Table.hpp"
#include "Event.hpp"
#include <queue>
#include <string>
#include <utility>
#include <vector>
#pragma once

class ComputerClub
{
public:
    ComputerClub() = default;

    ComputerClub(const std::vector<std::string> &clientsInClub, const std::queue<std::string> &clientQueue,
                 const std::vector<Table> &tables, const Time &openingTime, const Time &closingTime, int numOfTables,
                 int costPerHour) : clientsInClub(clientsInClub), clientQueue(clientQueue), tables(tables),
                                    openingTime(openingTime), closingTime(closingTime), numOfTables(numOfTables),
                                    costPerHour(costPerHour) {}

    void manageEvents(EventVisitor & visitor, const std::vector<Event *>& incomingEvents);
    int countRevenue();

    const Time &getOpeningTime() const {
        return openingTime;
    }

    void setOpeningTime(const Time &openingTime) {
        ComputerClub::openingTime = openingTime;
    }

    const Time &getClosingTime() const {
        return closingTime;
    }

    void setClosingTime(const Time &closingTime) {
        ComputerClub::closingTime = closingTime;
    }

    int getNumOfTables() const {
        return numOfTables;
    }

    void setNumOfTables(int numOfTables) {
        ComputerClub::numOfTables = numOfTables;
    }

    int getCostPerHour() const {
        return costPerHour;
    }

    void setCostPerHour(int costPerHour) {
        ComputerClub::costPerHour = costPerHour;
    }

    std::vector<std::string> clientsInClub;
    std::queue<std::string> clientQueue;
    std::vector<Table> tables;
private:
    Time openingTime;
    Time closingTime;
    int numOfTables;
    int costPerHour;
};