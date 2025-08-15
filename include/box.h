#ifndef BOX_H
#define BOX_H

class Box{

private:
    // int connections = CN_UP | CN_DOWN | CN_RIGHT | CN_LEFT;
    int connections = 0x0;


public:
    enum Conns{
        NILL        = 0x0,
        CN_UP       = 0x1,
        CN_DOWN     = 0x2,
        CN_RIGHT    = 0x4,
        CN_LEFT     = 0x8 
    };

    static Conns ijtoC(int i, int j){
        if (i == -1) return CN_UP;
        if (i == 1) return CN_DOWN;
        if (j == -1) return CN_LEFT;
        if (j == 1) return CN_RIGHT;

        return NILL;
    }

    bool connectedTo(Conns side);
    bool hasZeroConns();
    void disconnectSide(Conns side);
    void connectSide(Conns side);

};


#endif