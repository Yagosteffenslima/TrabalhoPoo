#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

// Classe que representa o relógio global
class RelogioGlobal {
private:
    static long dataAtual;

public:
    static void setData(long newData) {
        dataAtual = newData;
    }

    static long getData() {
        return dataAtual;
    }
};

long RelogioGlobal::dataAtual = 0;

// Classe abstrata que representa um evento no simulador
class Evento {
protected:
    int timeStamp;

public:
    Evento(int timeStamp) : timeStamp(timeStamp) {}

    int getTimeStamp() const {
        return timeStamp;
    }

    virtual void execute() const = 0;
};

// Classe Processo que herda de Evento
class Processo : public Evento {
private:
    int prioridade;
    int milhoesInstrucoes;
    int ram;
    double ioRate;

public:
    Processo(int timeStamp, int prioridade, int milhoesInstrucoes, int ram, double ioRate)
        : Evento(timeStamp), prioridade(prioridade), milhoesInstrucoes(milhoesInstrucoes), ram(ram), ioRate(ioRate) {}

    int getPrioridade() const {
        return prioridade;
    }

    int getMilhoesInstrucoes() const {
        return milhoesInstrucoes;
    }

    int getRam() const {
        return ram;
    }

    double getIoRate() const {
        return ioRate;
    }

    void execute() const override {
        std::cout << "Executando processo no timestamp: " << getTimeStamp() << std::endl;
        // Aqui você pode adicionar a lógica para executar o processo
    }
};

// Classe CPU
class CPU {
private:
    int velQuantumCPU;
    long tempoOciosidade;
    long tempoOcupacao;
    long ultimoUpdate;

public:
    CPU(int velCpu) : velQuantumCPU(velCpu), tempoOciosidade(0), tempoOcupacao(0), ultimoUpdate(0) {}

    int getVelQuantumCPU() const {
        return velQuantumCPU;
    }

    long getTempoOcioso() const {
        return tempoOciosidade;
    }

    long getTempoOcupado() const {
        return tempoOcupacao;
    }

    void setTempoOcupado(long tempoOcupado) {
        tempoOcupacao += tempoOcupado;
    }

    void setVelQuantumCPU(int velQuantumCPU) {
        this->velQuantumCPU = velQuantumCPU;
    }

    void atualizaTempos(bool ociosidade) {
        long tempoAtual = RelogioGlobal::getData();
        long deltaTempo = tempoAtual - ultimoUpdate;
        if (ociosidade) {
            tempoOciosidade += deltaTempo;
        } else {
            tempoOcupacao += deltaTempo;
        }
        ultimoUpdate = tempoAtual;
    }
};

// Classe Kernel
class Kernel {
private:
    std::priority_queue<const Processo*> filaEventos;
    std::vector<CPU> cpus;
    int tempoExecucaoTotal;

public:
    Kernel(const std::priority_queue<const Processo*>& filaEventos, const std::vector<CPU>& cpus)
        : filaEventos(filaEventos), cpus(cpus), tempoExecucaoTotal(0) {}

    void run() {
        while (!filaEventos.empty()) {
            const Processo* evento = filaEventos.top();
            filaEventos.pop();
            RelogioGlobal::setData(evento->getTimeStamp());

            if (cpus.empty()) {
                std::cout << "Nenhuma CPU disponível." << std::endl;
                continue;
            }

            CPU cpu = cpus.back();
            cpus.pop_back();

            long inicioExecucao = RelogioGlobal::getData() + std::time(nullptr);

            evento->execute();

            long fimExecucao = RelogioGlobal::getData() + std::time(nullptr);
            long tempoExecucaoEvento = fimExecucao - inicioExecucao;
            tempoExecucaoTotal += tempoExecucaoEvento;
            cpu.setTempoOcupado(tempoExecucaoTotal);

            cpus.push_back(cpu);
        }

        apresentarEstatisticas();
    }

    void apresentarEstatisticas() const {
        std::cout << "Estatísticas coletadas:" << std::endl;
        for (const CPU& cpu : cpus) {
            long tempoOciosidade = cpu.getTempoOcioso();
            long tempoOcupacao = cpu.getTempoOcupado();

            std::cout << "Tempo de ocupação da CPU: " << tempoOcupacao << " Unidades de tempo" << std::endl;
            std::cout << "Tempo de ociosidade da CPU: " << tempoOciosidade << " Unidades de tempo" << std::endl;
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return 1;
    }

    std::string arquivoCSV = argv[1];
    std::ifstream arquivo(arquivoCSV);

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << arquivoCSV << std::endl;
        return 1;
    }

    std::priority_queue<const Processo*> filaEventos;
    std::vector<CPU> cpus;
    std::string linha;

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            int timeStamp = std::stoi(tokens[0]);
            int prioridade = std::stoi(tokens[1]);
            int milhoesInstrucoes = std::stoi(tokens[2]);
            int ram = std::stoi(tokens[3]);
            double ioRate = std::stod(tokens[4]);

            Processo* processo = new Processo(timeStamp, prioridade, milhoesInstrucoes, ram, ioRate);
            filaEventos.push(processo);
        }
    }

    for (int i = 0; i < 4; i++) {
        cpus.push_back(CPU(4)); // Substitua 4 pela velocidade desejada da CPU
    }

    Kernel kernel(filaEventos, cpus);
    kernel.run();

    // Libera a memória dos processos
    while (!filaEventos.empty()) {
        delete filaEventos.top();
        filaEventos.pop();
    }

    return 0;
}
