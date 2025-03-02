#include "ProcessableEvent.hpp"
#pragma once

class ClientWaitEvent : public ProcessableEvent
{
public:
    explicit ClientWaitEvent(Time time, int eventId, const std::string &clientName) : ProcessableEvent(time, eventId, clientName) {}

    void process(EventVisitor & eventVisitor) override{
        eventVisitor.allEvents.push_back(this);
        eventVisitor.processClientWaitEvent(this->getTime(), this->getClientName());
    }
};