#include "Time.hpp"
#include <string>
#pragma once

class Event
{
public:
    virtual std::string toString() {
        return time.toString() + " " + std::to_string(id);
    }

    int getId() const { return id; }

    void setId(int id) { Event::id = id; }

    const Time &getTime() const { return time; }

    void setTime(const Time &t) { Event::time = t; }

    Event() = default;

    Event(const Time &time, int id) : time(time), id(id) {}

private:
    Time time;
    int id;
};