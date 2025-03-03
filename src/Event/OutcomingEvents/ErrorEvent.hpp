#include <Event.hpp>
#include <string>
#pragma once

class ErrorEvent : public Event
{
public:
    explicit ErrorEvent(Time time, int eventId, std::string errorName) : Event(time, eventId) , errorName(std::move(errorName)) {}

    std::string toString() override {
        std::string eventInfo = Event::toString();
        return eventInfo + " " + errorName;
    }

private:
    std::string errorName;
};