#ifndef KERNEL_H
#define KERNEL_H

#include <queue>
#include <vector>
#include "RelogioGlobal.h"
#include "CPU.h"
#include "Evento.h"

// Definição da classe Processo
class Processo {
    private:
    int ram;
public:
    Processo(int timeStamp, int ram);

    void execute();

    int getTimeStamp() const;

    int getRam() const;

};

// Definição da classe Kernel
class Kernel {
private:
    std::priority_queue<Processo*, std::vector<Processo*>, CompareProcesso>& filaEventos;
    int tamanhoRAM;
    int tamanhoSwap;
    CPU& cpu;
    int tempoExecucaoTotal;

    bool verificarMemoriaDisponivel(Processo* processo);
    void apresentarEstatisticas();

public:
    Kernel(std::priority_queue<Processo*, std::vector<Processo*>, CompareProcesso>& filaEventos, int tamanhoRAM, CPU& cpu);

    void run();
};

#endif
