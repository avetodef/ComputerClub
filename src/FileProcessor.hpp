#include "Event.hpp"
#include "ComputerClub.hpp"
#include <vector>
#include <string>
#pragma once

class FileProcessor {
public:
    FileProcessor() = default;

    explicit FileProcessor(const EventFactory &factory) : factory(factory) {}

    std::vector<Event *> processFile(std::string &fileName, ComputerClub &club);

private:
    EventFactory factory;

    static Time stringToTime(const std::string &s);

    static bool isValidClientName(const std::string &name);

    static bool isValidTimeFormat(const std::string &timeStr);
};