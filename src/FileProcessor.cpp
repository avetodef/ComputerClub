#include "FileProcessor.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <exception>

std::vector<Event*> FileProcessor::processFile(std::string &fileName, ComputerClub & club)
{
    std::vector<Event*> events;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    std::string line;
    if (std::getline(file, line)) {
        try {
            int numTables = std::stoi(line);
            if (numTables <= 0) {
                throw std::runtime_error(line);
            }
            club.setNumOfTables(numTables);
            for (int i = 1; i <= club.getNumOfTables(); ++i) {
                club.tables.emplace_back(i);
            }
        } catch (const std::invalid_argument&) {
            throw std::runtime_error(line);
        }
    } else {
        throw std::runtime_error("Failed to read number of tables from file!");
    }

    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string start, end;
        if (!(iss >> start >> end)) {
            throw std::runtime_error(line);
        }
        try {
            club.setOpeningTime(stringToTime(start));
            club.setClosingTime(stringToTime(end));
        } catch (const std::runtime_error& e) {
            throw std::runtime_error(line);
        }
    } else {
        throw std::runtime_error("Failed to read working hours from file!");
    }

    if (std::getline(file, line)) {
        try {
            int cost = std::stoi(line);
            if (cost <= 0) {
                throw std::runtime_error(line);
            }
            club.setCostPerHour(cost);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error(line);
        }
    } else {
        throw std::runtime_error("Failed to read cost per hour from file!");
    }

    Time prevEventTime(0, 0);
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string timeStr;
        int id;
        std::string clientName;
        if (!(iss >> timeStr >> id >> clientName)) {
            throw std::runtime_error(line);
        }

        Time eventTime;
        try {
            eventTime = stringToTime(timeStr);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error(line);
        }
        if (eventTime < prevEventTime) {
            throw std::runtime_error(line);
        }
        prevEventTime = eventTime;

        if (!isValidClientName(clientName)) {
            throw std::runtime_error(line);
        }

        Event* event;
        int tableId;
        if (id == 2) {
            if (!(iss >> tableId)) {
                throw std::runtime_error(line);
            }
            if (tableId < 1 || tableId > club.getNumOfTables()) {
                throw std::runtime_error(line);
            }
            event = factory.createEvent(eventTime, id, clientName, tableId);
        } else {
            event = factory.createEvent(eventTime, id, clientName);
        }
        events.push_back(event);
    }
    file.close();
    return events;
}

bool FileProcessor::isValidTimeFormat(const std::string& timeStr) {
    if (timeStr.length() != 5) return false;
    if (timeStr[2] != ':') return false;

    for (int i = 0; i < 2; ++i) {
        if (!isdigit(timeStr[i])) return false;
    }

    for (int i = 3; i < 5; ++i) {
        if (!isdigit(timeStr[i])) return false;
    }

    return true;
}

Time FileProcessor::stringToTime(const std::string& s) {
    if (!isValidTimeFormat(s)){
        throw std::runtime_error(s);
    }
    size_t colonPos = s.find(':');
    if (colonPos == std::string::npos || colonPos == 0 || colonPos == s.length() - 1) {
        throw std::runtime_error(s);
    }

    int h, m;
    try {
        h = std::stoi(s.substr(0, colonPos));
        m = std::stoi(s.substr(colonPos + 1));
    } catch (const std::invalid_argument&) {
        throw std::runtime_error(s);
    }

    if (h < 0 || h >= 24 || m < 0 || m >= 60) {
        throw std::runtime_error(s);
    }

    return Time(h, m);
}

bool FileProcessor::isValidClientName(const std::string &name) {
    for (char ch : name) {
        if (!(std::isalnum(ch) || ch == '_' || ch == '-')) {
            return false;
        }
    }
    return true;
}
