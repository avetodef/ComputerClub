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
    ComputerClub(std::vector<std::string> clientsInClub, std::queue<std::string> clientQueue,
                 std::vector<Table> tables, const Time &openingTime, const Time &closingTime, int numOfTables,
                 int costPerHour) : clientsInClub(std::move(clientsInClub)), clientQueue(std::move(clientQueue)), tables(std::move(tables)),
                                    openingTime(openingTime), closingTime(closingTime), numOfTables(numOfTables),
                                    costPerHour(costPerHour) {}


    const Time &getOpeningTime() const { return openingTime; }
    void setOpeningTime(const Time &time) { ComputerClub::openingTime = time; }

    const Time &getClosingTime() const { return closingTime; }
    void setClosingTime(const Time &time) { ComputerClub::closingTime = time; }

    int getNumOfTables() const { return numOfTables; }
    void setNumOfTables(int num) { ComputerClub::numOfTables = num; }

    int getCostPerHour() const { return costPerHour; }
    void setCostPerHour(int cost) { ComputerClub::costPerHour = cost; }

    void manageEvents(EventVisitor & visitor, const std::vector<Event *>& incomingEvents);

    std::vector<std::string> clientsInClub;
    std::queue<std::string> clientQueue;
    std::vector<Table> tables;
private:
    Time openingTime;
    Time closingTime;
    int numOfTables;
    int costPerHour;
};