#include <Event.hpp>
#include <string>
#include <utility>
#pragma once

class ClientKickedOutEvent : public Event
{
public:
    explicit ClientKickedOutEvent(Time time, int eventId, std::string clientName) : Event(time, eventId) , clientName(std::move(clientName)) {}

    std::string toString() override {
        std::string eventInfo = Event::toString();
        return eventInfo + " " + clientName;
    }

private:
    std::string clientName;
};