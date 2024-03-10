#ifndef CPU_H
#define CPU_H
#include "RelogioGlobal.h"

class CPU {
private:
    int velQuantumCPU;
    long tempoOcioso;
    long tempoOcupado;
    long lastUpdate;
    RelogioGlobal* relGlobal;

public:
    CPU(int velocidadeCPU, RelogioGlobal* relGlobglob);

    int getVelQuantumCPU();

    long getTempoOcioso();

    long getTempoOcupado();

    void setTempoOcupado(long tempoOcupado);

    void setVelQuantumCPU(int velQuantumCPU);

    // função para atualizar o tempo atual
    void attTempo(bool ocioso);
};

#endif
