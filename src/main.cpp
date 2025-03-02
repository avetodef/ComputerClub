#include <iostream>
#include "FileProcessor.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "No event file provided!" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];

    EventFactory factory;
    FileProcessor processor(factory);

    ComputerClub club;
    std::vector<Event *> incomingEvents;

    try
    {
        incomingEvents = processor.processFile(fileName, club);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::vector<Event *> allEvents;
    EventVisitor visitor(allEvents, factory, &club);

    club.manageEvents(visitor, incomingEvents);

    std::cout << club.getOpeningTime().toString() << std::endl;
    for (auto event : visitor.allEvents){
        std::cout << event->toString() << std::endl;
    }
    std::cout << club.getClosingTime().toString() << std::endl;
    for (auto table : club.tables){
        std::cout << table.toString() << std::endl;
    }

    for (Event* event : allEvents) {
        delete event;
    }
    allEvents.clear();

    for (Event* event : incomingEvents) {
        delete event;
    }
    incomingEvents.clear();
    return 0;
}
