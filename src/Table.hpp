#include <string>
#include <utility>
#include "Time.hpp"
#pragma once

class Table
{
public:
    Table() = default;
    explicit Table(int id) : id(id) {}
    Table(int id, std::string clientName, const Time &occupiedFrom) : id(id), clientName(std::move(clientName)),
                                                                             occupiedFrom(occupiedFrom) {}
    Table(int id, std::string clientName, const Time &occupiedFrom, const Time &totalTimeOccupied,
          int totalRevenue) : id(id), clientName(std::move(clientName)), occupiedFrom(occupiedFrom),
                              totalTimeOccupied(totalTimeOccupied), totalRevenue(totalRevenue) {}



    int getId() const { return id; }
    void setId(int id) { Table::id = id; }

    const std::string &getClientName() const { return clientName; }
    void setClientName(const std::string &clientName) {Table::clientName = clientName; }

    const Time &getOccupiedFrom() const { return occupiedFrom; }
    void setOccupiedFrom(const Time &occupiedFrom) { Table::occupiedFrom = occupiedFrom; }

    const Time &getTotalTimeOccupied() const { return totalTimeOccupied; }
    void setTotalTimeOccupied(const Time &totalTimeOccupied) { Table::totalTimeOccupied = totalTimeOccupied; }

    int getTotalRevenue() const { return totalRevenue; }
    void setTotalRevenue(int revenue) { Table::totalRevenue = revenue; }

    void freeTable();
    void updateTotalTimeOccupied(Time end);
    int countRevenue(Time from, Time to, int cost);
    std::string toString();

private:
    int id;
    std::string clientName;
    Time occupiedFrom;
    Time totalTimeOccupied;
    int totalRevenue;
};