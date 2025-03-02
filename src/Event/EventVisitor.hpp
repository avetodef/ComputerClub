#include "Event.hpp"
#include "EventFactory.hpp"
#include <vector>
#include <string>
#pragma once

class ComputerClub;
class EventVisitor
{
public:
    EventVisitor(const std::vector<Event *> &allEvents, const EventFactory &factory, ComputerClub *club) : allEvents(
            allEvents), factory(factory), club(club) {}

    void processClientArrived(Time time, const std::string& clientName);
    void processTableTakenEvent(Time time, const std::string& clientName, int tableId);
    void processClientWaitEvent(Time time, const std::string& clientName);
    void processClientLeftEvent(Time time, const std::string& clientName);

    EventFactory &getFactory() {
        return factory;
    }

    void setFactory(const EventFactory &factory) {
        EventVisitor::factory = factory;
    }

    ComputerClub *getClub() const {
        return club;
    }

    void setClub(ComputerClub *club) {
        EventVisitor::club = club;
    }

    std::vector<Event*> allEvents;
private:
    EventFactory factory;
    ComputerClub* club;
};