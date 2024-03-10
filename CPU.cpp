#include "cpu.h"

// Implementação da função getData da classe RelogioGlobal
long RelogioGlobal::getData() {
 
    return 0; 
}

// Implementação do construtor da classe CPU
CPU::CPU(int velocidadeCPU, RelogioGlobal* relGlobglob) : velQuantumCPU(velocidadeCPU), tempoOcioso(0), tempoOcupado(0), lastUpdate(0), relGlobal(relGlobglob) {}

// Implementação dos métodos get e set da classe CPU
int CPU::getVelQuantumCPU() {
    return velQuantumCPU;
}

long CPU::getTempoOcioso() {
    return tempoOcioso;
}

long CPU::getTempoOcupado() {
    return tempoOcupado;
}

void CPU::setTempoOcupado(long tempoOcupado) {
    this->tempoOcupado += tempoOcupado;
}

void CPU::setVelQuantumCPU(int velQuantumCPU) {
    this->velQuantumCPU = velQuantumCPU;
}

// Implementação da função para atualizar o tempo atual da CPU
void CPU::attTempo(bool ocioso) {
    long TempoAtual = relGlobal->getData();
    long DiffTempo = TempoAtual - lastUpdate;
    if (ocioso) {
        tempoOcioso += DiffTempo;
    } else {
        tempoOcupado += DiffTempo;
    }
    lastUpdate = TempoAtual;
}
