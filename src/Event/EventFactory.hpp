#include <Event.hpp>
#include <ErrorEvent.hpp>
#include "Time.hpp"
#include <string>
#pragma once

class EventFactory
{
public:
    EventFactory() = default;

    static Event * createEvent(Time time, int eventId, std::string  clientName);
    static Event * createEvent(Time time, int eventId, std::string clientName, int tableId);
    static ErrorEvent * createErrorEvent(Time time, std::string  errorName);
};