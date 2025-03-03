#include "Time.hpp"
#include <string>
#pragma once

class Event
{
public:
    Event() = default;
    Event(const Time &time, int id) : time(time), id(id) {}

    virtual std::string toString() {
        return time.toString() + " " + std::to_string(id);
    }

    int getId() const { return id; }
    void setId(int id) { Event::id = id; }

    const Time &getTime() const { return time; }
    void setTime(const Time &t) { Event::time = t; }

private:
    Time time;
    int id;
};