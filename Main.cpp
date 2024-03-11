#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include "RelogioGlobal.h"
#include "Evento.h"
#include "Kernel.h"
#include "CPU.h"


std::priority_queue<Processo> lerArquivoCSV(const std::string& arquivoCSV) {
    std::priority_queue<Processo> filaEventos;

    std::ifstream file(arquivoCSV);
    std::string linha;

    while (std::getline(file, linha)) {
        if (linha[0] != '#') { // Ignora linhas que começam com #
            std::stringstream ss(linha);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            int timestamp = std::stoi(tokens[0]);
            int prioridade = std::stoi(tokens[1]);
            int mi = std::stoi(tokens[2]);
            int ram = std::stoi(tokens[3]);
            double ioRate = std::stod(tokens[4]);

            filaEventos.push(Processo(timestamp, prioridade, mi, ram, ioRate));
        }
    }

    return filaEventos;
}

int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos é válido
    if (argc != 2) {
        std::cout << "Uso: ./main <arquivo.csv>" << std::endl;
        return 1;
    }

    // Obtém o caminho do arquivo CSV a partir dos argumentos
    std::string arquivoCSV = argv[1];
    // Lê o arquivo CSV e cria a fila de eventos
    std::priority_queue<Processo> filaEventos = lerArquivoCSV(arquivoCSV);
    // Instancia o Relogio Global
    RelogioGlobal relGlobal;
    // Instancia a lista de CPUS
    std::vector<CPU> cpus;
    for (int i = 0; i < 4; i++) {
        cpus.push_back(CPU(4, relGlobal)); // Substitua 1 pela velocidade desejada da CPU
    }
    // Cria uma instância do Kernel com a fila de eventos
    Kernel kernel(filaEventos, relGlobal, 8, cpus);
    // Executa a simulação
    kernel.run();

    return 0;
}
