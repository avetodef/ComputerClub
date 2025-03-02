#include "EventVisitor.hpp"
#include "ComputerClub.hpp"
#include <algorithm>
#include <iostream> // For logging

//Формат: <время> 1 <имя клиента>
//Если клиент уже в компьютерном клубе, генерируется ошибка "YouShallNotPass"
//Если клиент пришел в нерабочие часы, тогда "NotOpenYet"
void EventVisitor::processClientArrived(Time time, const std::string& clientName) {

    if (time < club->getOpeningTime()) {
        allEvents.push_back(factory.createErrorEvent(time, "NotOpenYet"));
        return;
    }

    if (std::find(club->clientsInClub.begin(), club->clientsInClub.end(), clientName) != club->clientsInClub.end()) {
        allEvents.push_back(factory.createErrorEvent(time, "YouShallNotPass"));
        return;
    }

    club->clientsInClub.push_back(clientName);
}

//ID 2. Клиент сел за стол
//Формат: <время> 2 <имя клиента> <номер стола>
//Если клиент уже сидит за столом, то он может сменить стол.
//Если стол <номер стола> занят (в том числе, если клиент пытается пересесть за стол, за которым сам и сидит), генерируется ошибка "PlaceIsBusy".
//Если клиент не находится в компьютерном клубе, генерируется ошибка "ClientUnknown".
void EventVisitor::processTableTakenEvent(Time time, const std::string& clientName, int tableId) {
    if (std::find(club->clientsInClub.begin(), club->clientsInClub.end(), clientName) == club->clientsInClub.end()) {
        allEvents.push_back(factory.createErrorEvent(time, "ClientUnknown"));
        return;
    }

    auto tableIt = std::find_if(club->tables.begin(), club->tables.end(), [tableId](const Table & table) { return table.getId() == tableId; });
    if (!tableIt->getClientName().empty()) {
        allEvents.push_back(factory.createErrorEvent(time, "PlaceIsBusy"));
        return;
    }

    // Client is in the club
    auto prevTable = std::find_if(club->tables.begin(), club->tables.end(), [clientName](const Table & table) { return table.getClientName() == clientName; });
    if (prevTable != club->tables.end()) { // Client already sits
        prevTable->countRevenue(prevTable->getOccupiedFrom(), time, club->getCostPerHour());
        prevTable->freeTable();
    }

    tableIt->setClientName(clientName);
    tableIt->setOccupiedFrom(time);
}

//ID 3. Клиент ожидает
//Формат: <время> 3 <имя клиента>
//Если в клубе есть свободные столы, то генерируется ошибка "ICanWaitNoLonger!".
//Если в очереди ожидания клиентов больше, чем общее число столов, то клиент уходит и генерируется событие ID 11.
void EventVisitor::processClientWaitEvent(Time time, const std::string& clientName) {

    auto emptyTable = std::find_if(club->tables.begin(), club->tables.end(), [](const Table & table) { return table.getClientName().empty(); });
    if (emptyTable != club->tables.end()) { // There is at least one free table
        allEvents.push_back(factory.createErrorEvent(time, "ICanWaitNoLonger!"));
        return;
    }

    if (club->clientQueue.size() >= club->tables.size()) {
        allEvents.push_back(factory.createEvent(time, 11, clientName));
        club->clientsInClub.erase(std::remove(club->clientsInClub.begin(), club->clientsInClub.end(), clientName), club->clientsInClub.end());
        return;
    }

    club->clientQueue.push(clientName);
}

//ID 4. Клиент ушел
//Формат: <время> 4 <имя клиента>
//Если клиент не находится в компьютерном клубе, генерируется ошибка "ClientUnknown".
//Когда клиент уходит, стол, за которым он сидел освобождаться и его занимает первый клиент из очереди ожидания (ID 12).
void EventVisitor::processClientLeftEvent(Time time, const std::string& clientName) {

    if (std::find(club->clientsInClub.begin(), club->clientsInClub.end(), clientName) == club->clientsInClub.end()) {
        allEvents.push_back(factory.createErrorEvent(time, "ClientUnknown"));
        return;
    }

    club->clientsInClub.erase(std::remove(club->clientsInClub.begin(), club->clientsInClub.end(), clientName), club->clientsInClub.end());

    auto tableIt = std::find_if(club->tables.begin(), club->tables.end(), [clientName](const Table & table) { return table.getClientName() == clientName; });
    tableIt->countRevenue(tableIt->getOccupiedFrom(), time, club->getCostPerHour());
    tableIt->updateTotalTimeOccupied(time);
    tableIt->freeTable();

    if (!club->clientQueue.empty()) {
        std::string firstInQueue = club->clientQueue.front();
        club->clientQueue.pop();
        tableIt->setClientName(firstInQueue);
        tableIt->setOccupiedFrom(time);
        allEvents.push_back(factory.createEvent(time, 12, firstInQueue, tableIt->getId()));
    }
}