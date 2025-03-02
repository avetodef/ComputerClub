#include <string>
#include "Time.hpp"
#pragma once

class Table
{
public:

    void freeTable();
    void updateTotalTimeOccupied(Time end);
    int countRevenue(Time from, Time to, int cost);
    std::string toString();
    std::string debugInfo();

    Table() = default;

    explicit Table(int id) : id(id) {}

    Table(int id, const std::string &clientName, const Time &occupiedFrom) : id(id), clientName(clientName),
                                                                             occupiedFrom(occupiedFrom) {}

    Table(int id, const std::string &clientName, const Time &occupiedFrom, const Time &totalTimeOccupied,
          int totalRevenue) : id(id), clientName(clientName), occupiedFrom(occupiedFrom),
                              totalTimeOccupied(totalTimeOccupied), totalRevenue(totalRevenue) {}


    int getId() const {
        return id;
    }

    void setId(int id) {
        Table::id = id;
    }

    const std::string &getClientName() const {
        return clientName;
    }

    void setClientName(const std::string &clientName) {
        Table::clientName = clientName;
    }

    const Time &getOccupiedFrom() const {
        return occupiedFrom;
    }

    void setOccupiedFrom(const Time &occupiedFrom) {
        Table::occupiedFrom = occupiedFrom;
    }

    const Time &getTotalTimeOccupied() const {
        return totalTimeOccupied;
    }

    void setTotalTimeOccupied(const Time &totalTimeOccupied) {
        Table::totalTimeOccupied = totalTimeOccupied;
    }

    int getTotalRevenue() const {
        return totalRevenue;
    }

    void setTotalRevenue(int totalRevenue) {
        Table::totalRevenue = totalRevenue;
    }

private:
    int id;
    std::string clientName;
    Time occupiedFrom;
    Time totalTimeOccupied;
    int totalRevenue;
};