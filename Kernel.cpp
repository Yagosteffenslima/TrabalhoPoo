#include "Kernel.h"
#include <iostream>

// Implementação do método run da classe Kernel
void Kernel::run() {
    while (!filaEventos.empty()) {
        Processo* evento = filaEventos.top();
        filaEventos.pop();

        long inicioExecucao = std::clock();

        if (verificarMemoriaDisponivel(evento)) {
            CPU->atualizaTempos(false);
            evento->execute();
            CPU->atualizaTempos(true);
            long fimExecucao = std::clock();
            long tempoExecucaoEvento = fimExecucao - inicioExecucao;
            tempoExecucaoTotal += tempoExecucaoEvento;
            CPU->setTempoOcupado(tempoExecucaoTotal);
        } else {
            // Se não houver memória disponível, o evento é ignorado
            std::cout << "Ignorando evento devido à falta de memória." << std::endl;
        }
    }

    apresentarEstatisticas();
}

// Implementação da função privada verificarMemoriaDisponivel da classe Kernel
bool Kernel::verificarMemoriaDisponivel(Processo* processo) {
    if (processo->getRam() > tamanhoRAM) {
        return false;
    } else {
        tamanhoRAM -= processo->getRam();
        return true;
    }
}

// Implementação da função privada apresentarEstatisticas da classe Kernel
void Kernel::apresentarEstatisticas() {
    // Implementação da apresentação de estatísticas
}
