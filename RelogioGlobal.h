#ifndef RELOGIO_GLOBAL_H
#define RELOGIO_GLOBAL_H

class RelogioGlobal {
private:
    static long dataAtual;

public:
    static void setData(long newData);

    static long getData();
};

#endif
