#include "EventVisitor.hpp"
#include <string>
#include <utility>
#pragma once

class ProcessableEvent : public Event
{
public:
    virtual void process(EventVisitor & eventVisitor) = 0;

    std::string getClientName() { return clientName; }

    void setClientName(const std::string &clientName) { ProcessableEvent::clientName = clientName; }

    virtual ~ProcessableEvent() = default;

    ProcessableEvent(Time time, int eventId, std::string clientName) : Event(time, eventId), clientName(std::move(clientName)) {}

    std::string toString() override {
        std::string eventInfo = Event::toString();
        return eventInfo + " " + clientName;
    }
private:
    std::string clientName;
};