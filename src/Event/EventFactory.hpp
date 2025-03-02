#include <Event.hpp>
#include <ErrorEvent.hpp>
#include "Time.hpp"
#include <string>
#pragma once

class EventFactory
{
public:
    EventFactory();

    Event * createEvent(Time time, int eventId, std::string clientName);
    Event * createEvent(Time time, int eventId, std::string clientName, int tableId);
    ErrorEvent * createErrorEvent(Time time, std::string errorName);
};