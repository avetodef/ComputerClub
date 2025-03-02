#include "ProcessableEvent.hpp"
#pragma once

class ClientLeftEvent : public ProcessableEvent
{
public:
    explicit ClientLeftEvent(Time time, int eventId, const std::string &clientName) : ProcessableEvent(time, eventId, clientName) {}

    void process(EventVisitor & eventVisitor) override{
        eventVisitor.allEvents.push_back(this);
        eventVisitor.processClientLeftEvent(this->getTime(), this->getClientName());
    }
};