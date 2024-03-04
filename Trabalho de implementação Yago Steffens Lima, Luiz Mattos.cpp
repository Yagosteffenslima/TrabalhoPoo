// Nomes: Yago Steffens Lima, Luis Felipe Mattos


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

// Classe para representar um processo
class Processo {
private:
    int timestamp;
    int prioridade;
    int milhoesInstrucoes;
    int memoriaRAM;
    int ioRate;

public:
    Processo(int timestamp, int prioridade, int milhoesInstrucoes, int memoriaRAM, int ioRate)
        : timestamp(timestamp), prioridade(prioridade), milhoesInstrucoes(milhoesInstrucoes), memoriaRAM(memoriaRAM), ioRate(ioRate) {}

    // Getters
    int getPrioridade() const {
        return prioridade;
    }
};

// Classe para representar um evento
class Evento {
private:
    int timestamp;

public:
    Evento(int timestamp) : timestamp(timestamp) {}

    int getTimestamp() const {
        return timestamp;
    }

    // Método virtual para processar o evento
    virtual void process() = 0;

    bool operator<(const Evento& other) const {
        return timestamp > other.timestamp; // Ordem decrescente
    }
};

// Classe para representar o evento de chegada de um processo
class EventoChegadaProcesso : public Evento {
private:
    Processo* processo;

public:
    EventoChegadaProcesso(int timestamp, Processo* processo) : Evento(timestamp), processo(processo) {}

    void process() override {
        ProcessosProntos.push_back(processo);
    }
};

// Classe para representar um evento de término de E/S
class EventoTerminoIO : public Evento {
private:
    Processo* processo;

public:
    EventoTerminoIO(int timestamp, Processo* processo) : Evento(timestamp), processo(processo) {}

    void process() override {
        ProcessosProntos.push_back(processo);
    }
};

// Interface para definir uma política de escalonamento
class PoliticaEscalonamento {
public:
    virtual void escalonar(std::vector<Processo*>& processosProntos) = 0;
};

// Implementação de uma política de escalonamento (exemplo)
class PoliticaPrioridade : public PoliticaEscalonamento {
public:
    void escalonar(std::vector<Processo*>& processosProntos) override {
        std::sort(processosProntos.begin(), processosProntos.end(), [](const Processo* a, const Processo* b) {
            return a->getPrioridade() > b->getPrioridade(); // Ordena em ordem decrescente de prioridade
        });
        // Lógica para escalonar os processos
    }
};

// Classe para representar uma CPU
class CPU {
private:
    int velocidade;
    bool ocupada;
    Processo* processoAtual;

public:
    CPU(int velocidade) : velocidade(velocidade), ocupada(false), processoAtual(nullptr) {}

    bool isOcupada() const {
        return ocupada;
    }

    void executarProcesso(Processo* processo) {
        ocupada = true;
        processoAtual = processo;
        // Implemente a lógica para executar o processo na CPU
    }
};

// Classe para representar a memória do sistema
class Memoria {
private:
    int tamanhoTotal;
    int tamanhoDisponivel;

public:
    Memoria(int tamanhoGB) : tamanhoTotal(tamanhoGB), tamanhoDisponivel(tamanhoGB) {}

    // Métodos para alocar e desalocar memória
};

// Lista de processos prontos
std::vector<Processo*> ProcessosProntos;

// Lista de CPUs
std::vector<CPU*> CPUs;

// Função para ler os processos de um arquivo CSV
std::vector<Processo*> lerProcessosDoCSV(const std::string& arquivoCSV) {
    std::vector<Processo*> processos;
    std::ifstream arquivo(arquivoCSV);
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        int timestamp, prioridade, milhoesInstrucoes, memoriaRAM, ioRate;
        char virgula;
        if (!(iss >> timestamp >> virgula >> prioridade >> virgula >> milhoesInstrucoes >> virgula >> memoriaRAM >> virgula >> ioRate)) {
            break;
        }
        processos.push_back(new Processo(timestamp, prioridade, milhoesInstrucoes, memoriaRAM, ioRate));
    }
    return processos;
}

// Função para simular o sistema
void simularSistema(std::vector<Processo*>& processos, PoliticaEscalonamento* escalonador,
                    int numCPUs, int velocidadeCPU, int memoriaGB, int quantumMS) {
    // Inicializa o sistema com o número correto de CPUs e a quantidade de memória especificada
    inicializarSistema(numCPUs, velocidadeCPU, memoriaGB);

    // Cria uma fila de eventos futuros
    std::priority_queue<Evento*> eventosFuturos;
    for (Processo* processo : processos) {
        eventosFuturos.push(new EventoChegadaProcesso(processo->getTimestamp(), processo));
    }

    int relGlobal = 0;

    // Processa os eventos futuros até que não haja mais eventos
    while (!eventosFuturos.empty()) {
        Evento* evento = eventosFuturos.top();
        eventosFuturos.pop();
        relGlobal = evento->getTimestamp();
        evento->process();
        // Implemente o restante da lógica do algoritmo de simulação
    }
}

// Função para inicializar o sistema com CPUs e memória
void inicializarSistema(int numCPUs, int velocidadeCPU, int memoriaGB) {
    for (int i = 0; i < numCPUs; i++) {
        CPUs.push_back(new CPU(velocidadeCPU));
    }
    // Inicialize a memória
}

// Função para apresentar os resultados
void apresentarResultados() {
    // Implemente a lógica para apresentar os resultados da simulação
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Uso: ./main arquivo.csv num_cpus velocidade_cpu memoria_gb quantum_ms\n";
        return 1;
    }

    std::string arquivoCSV = argv[1];
    int numCPUs = std::stoi(argv[2]);
    int velocidadeCPU = std::stoi(argv[3]);
    int memoriaGB = std::stoi(argv[4]);
    int quantumMS = std::stoi(argv[5]);

        // Lê os processos do arquivo CSV
    std::vector<Processo*> processos = lerProcessosDoCSV(arquivoCSV);

       // Cria um escalonador com uma política de escalonamento por prioridade
    PoliticaEscalonamento* escalonador = new PoliticaPrioridade();

    // Simula o sistema
    simularSistema(processos, escalonador, numCPUs, velocidadeCPU, memoriaGB, quantumMS);

    // Apresenta os resultados
    apresentarResultados();

    // Libera a memória alocada para os processos e o escalonador
    for (Processo* processo : processos) {
        delete processo;
    }
    delete escalonador;

    // Libera a memória alocada para as CPUs
    for (CPU* cpu : CPUs) {
        delete cpu;
    }

    return 0;
}
