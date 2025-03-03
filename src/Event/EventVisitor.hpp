#include "Event.hpp"
#include "EventFactory.hpp"
#include <utility>
#include <vector>
#include <string>
#pragma once

class ComputerClub;
class EventVisitor
{
public:
    EventVisitor() = default;
    EventVisitor(std::vector<Event *> allEvents, const EventFactory &factory, ComputerClub *club) : allEvents(std::move(
            allEvents)), factory(factory), club(club) {}

    EventFactory &getFactory() { return factory; }

    void processClientArrived(Time time, const std::string& clientName);
    void processTableTakenEvent(Time time, const std::string& clientName, int tableId);
    void processClientWaitEvent(Time time, const std::string& clientName);
    void processClientLeftEvent(Time time, const std::string& clientName);

    std::vector<Event*> allEvents;
private:
    EventFactory factory;
    ComputerClub* club;
};