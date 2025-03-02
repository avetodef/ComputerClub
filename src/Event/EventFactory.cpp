#include "EventFactory.hpp"
#include "ClientArrivedEvent.hpp"
#include "ClientWaitEvent.hpp"
#include "ClientLeftEvent.hpp"
#include "TableTakenEvent.hpp"
#include "ClientKickedOutEvent.hpp"
#include "ClientOccupiedTableEvent.hpp"

Event * EventFactory::createEvent(Time time, int eventId, std::string clientName){
    switch (eventId) {
        case 1:
            return new ClientArrivedEvent(time, eventId, clientName);
        case 2:
            break;
        case 3:
            return new ClientWaitEvent(time, eventId, clientName);
        case 4:
            return new ClientLeftEvent(time, eventId, clientName);
        case 11:
            return new ClientKickedOutEvent(time, eventId, clientName);
        case 12:
            break;
        default:
            return new ErrorEvent(time, 13, "UnknownEvent, event id: " + std::to_string(eventId));
    }
    return new Event(time, eventId);
}
Event * EventFactory::createEvent(Time time, int eventId, std::string clientName, int tableId){
    if (eventId == 2){
        return new TableTakenEvent(time, eventId, clientName, tableId);
    }
    if (eventId == 12){
        return new ClientOccupiedTableEvent(time, eventId, clientName, tableId);
    }
    return new ErrorEvent(time, 13, "UnknownEvent");
}

ErrorEvent * EventFactory::createErrorEvent(Time time, std::string errorName){
    return new ErrorEvent(time, 13, errorName);
}

EventFactory::EventFactory() {}
