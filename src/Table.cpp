#include "Table.hpp"
#include <iostream>

void Table::freeTable(){
    clientName = "";
    occupiedFrom = Time();
}

//За каждый час, проведённый за столом, клиент платит цену, указанную в конфигурации.
//При оплате время округляется до часа в большую сторону поэтому
//даже если клиент занимал стол всего несколько минут, он платит за целый час.
//Выручка – сумма, полученная ото всех клиентов за всё время работы компьютерного клуба.
int Table::countRevenue(Time from, Time to, int cost){
    Time totalTime = to - from;
    int hours = totalTime.getHour();
    if (totalTime.getMin() > 0) {
        hours += 1;
    }
    totalRevenue += hours * cost;
    return hours * cost;
}

std::string Table::toString() {
    return std::to_string(id) +  " " + std::to_string(totalRevenue) + " " + totalTimeOccupied.toString();
}

void Table::updateTotalTimeOccupied(Time end) {
    Time timeOfOneClient = end - occupiedFrom;
    totalTimeOccupied = totalTimeOccupied + timeOfOneClient;
}

std::string Table::debugInfo() {
    return std::to_string(id) + " " + clientName  + " " + occupiedFrom.toString() + " " + std::to_string(totalRevenue) + " " + totalTimeOccupied.toString();

}
