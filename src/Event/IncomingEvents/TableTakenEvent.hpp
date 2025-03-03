#include "ProcessableEvent.hpp"
#pragma once

class TableTakenEvent : public ProcessableEvent
{
public:
    explicit TableTakenEvent(Time time, int eventId, const std::string &clientName, int tableId) : ProcessableEvent(time, eventId, clientName) , tableId(tableId) {}

    int getTableId() const { return tableId; }
    void setTableId(int tableId) { TableTakenEvent::tableId = tableId; }

    void process(EventVisitor & eventVisitor) override{
        eventVisitor.allEvents.push_back(this);
        eventVisitor.processTableTakenEvent(this->getTime(), this->getClientName(), getTableId());
    }

    std::string toString() override {
        std::string eventInfo = ProcessableEvent::toString();
        return eventInfo + " " + std::to_string(tableId);
    }

private:
    int tableId;
};