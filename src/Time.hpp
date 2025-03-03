#include <string>
#pragma once

class Time
{
public:
    Time() = default;
    Time(int h, int m) : hour(h), min(m) {}

    int getHour() const { return hour; }
    void setHour(int h) { Time::hour = h; }

    int getMin() const { return min; }
    void setMin(int min) { Time::min = min; }

    std::string toString() const {
        return (hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
               (min < 10 ? "0" : "") + std::to_string(min);
    }

    bool operator==(const Time& other) const { return hour == other.hour && min == other.min; }
    bool operator!=(const Time& other) const { return !(*this == other); }
    bool operator<(const Time& other) const {
        if (hour < other.hour) return true;
        if (hour == other.hour && min < other.min) return true;
        return false;
    }
    bool operator>(const Time& other) const { return other < *this; }
    bool operator<=(const Time& other) const { return !(*this > other); }
    bool operator>=(const Time& other) const { return !(*this < other); }
    Time operator+(const Time& other) const {
        int totalMin = (hour + other.hour) * 60 + min + other.min;
        return Time(totalMin / 60, totalMin % 60);
    }
    Time operator-(const Time& other) const {
        int totalMin = (hour - other.hour) * 60 + min - other.min;
        if (totalMin < 0) totalMin += 24 * 60; // Обработка отрицательного времени
        return Time(totalMin / 60, totalMin % 60);
    }

private:
    int hour;
    int min;
};
