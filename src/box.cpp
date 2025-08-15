#include "box.h"

bool Box::connectedTo(Conns side){
    //maybe i should not make NILL 0x0
    if (side == NILL) return true;
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