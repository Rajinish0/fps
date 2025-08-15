#include "box.h"

bool Box::connectedTo(Conns side){
        return connections & side;
}

bool Box::hasZeroConns(){
    return connections == 0;
}

void Box::disconnectSide(Conns side){
    connections &= ~(side);
}

void Box::connectSide(Conns side){
    connections |= side;
}