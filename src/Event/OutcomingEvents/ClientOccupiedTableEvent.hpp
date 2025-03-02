#include <Event.hpp>
#include <string>
#pragma once

class ClientOccupiedTableEvent : public Event
{
public:
    explicit ClientOccupiedTableEvent(Time time, int eventId, std::string clientName, int table) : Event(time, eventId) , clientName(std::move(clientName)), tableId(table) {}
    std::string toString() override {
        std::string eventInfo = Event::toString();
        return eventInfo + " " + clientName + " " + std::to_string(tableId);
    }
private:
    std::string clientName;
    int tableId;
};