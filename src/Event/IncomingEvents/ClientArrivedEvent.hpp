#include "ProcessableEvent.hpp"
#include "iostream"
#pragma once

class ClientArrivedEvent : public ProcessableEvent
{
public:
    explicit ClientArrivedEvent(Time time, int eventId, std::string &clientName) : ProcessableEvent(time, eventId, clientName) {}

    void process(EventVisitor & eventVisitor) override{
        eventVisitor.allEvents.push_back(this);
        eventVisitor.processClientArrived(this->getTime(), this->getClientName());
    }
};