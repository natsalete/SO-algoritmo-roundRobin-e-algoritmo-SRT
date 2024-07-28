#include <iostream>
#include <locale>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Função de comparação para ordenar os processos pelo tempo de chegada
bool ordena(pair<char, pair<int, int>> a, pair<char, pair<int, int>> b) {
    return a.second.second < b.second.second;
}

void SRT() {
    cout << "Algoritmo Shortest Remaining Time (SRT)!" << endl << endl;

    vector<pair<char, pair<int, int>>> processosSRT; // Vetor de processos (nome, (tempo de processamento, tempo de chegada))
    int qtdEntradasSRT;

    // Solicita a quantidade de processos a serem inseridos
    do {
        cout << "Quantos processos quer inserir?" << endl;
        cin >> qtdEntradasSRT;
        if (qtdEntradasSRT > 15) {
            cout << endl << "Você pode inserir no máximo 15 processos!!" << endl << endl;
        }
    } while (qtdEntradasSRT > 15);

    processosSRT.resize(qtdEntradasSRT);

    // Lê os dados dos processos
    for (int i = 0; i < qtdEntradasSRT; i++) {
        cout << endl << "Insira o ID do processo, tempo de chegada e tempo de execução:" << endl;
        cin >> processosSRT[i].first >> processosSRT[i].second.first >> processosSRT[i].second.second;
    }

    // Ordena os processos pelo tempo de chegada
    sort(processosSRT.begin(), processosSRT.end(), ordena);

    // Fila de prioridade para processos (tempo de processamento restante, tempo de chegada, nome do processo)
    priority_queue<pair<int, pair<int, char>>, vector<pair<int, pair<int, char>>>, greater<pair<int, pair<int, char>>>> filaPrioridadeSRT;
    vector<pair<int, char>> saidaSRT; // Vetor para armazenar a sequência de execução dos processos (tempo, nome)
    int tempoSRT = 0; // Tempo atual
    bool executandoSRT = true; // Flag de controle do loop principal

    while (executandoSRT) {
        // Adiciona processos à fila de prioridade conforme o tempo de chegada
        for (int i = 0; i < processosSRT.size();) {
            if (processosSRT[i].second.second <= tempoSRT) {
                filaPrioridadeSRT.push({processosSRT[i].second.first, {processosSRT[i].second.second, processosSRT[i].first}});
                processosSRT.erase(processosSRT.begin() + i);
            } else {
                i++;
            }
        }

        if (!filaPrioridadeSRT.empty()) {
            auto processoAtualSRT = filaPrioridadeSRT.top();
            filaPrioridadeSRT.pop();

            // Executa o processo com o menor tempo restante por um tique de relógio
            saidaSRT.push_back({tempoSRT, processoAtualSRT.second.second}); // Armazena o tempo atual e o nome do processo
            tempoSRT++;

            // Reduz o tempo restante do processo em 1
            processoAtualSRT.first--;

            // Se o processo ainda não terminou, coloca-o de volta na fila de prioridade
            if (processoAtualSRT.first > 0) {
                filaPrioridadeSRT.push(processoAtualSRT);
            }
        } else {
            // Se não há processos prontos, incrementa o tempo sem executar nada
            saidaSRT.push_back({tempoSRT, '*'});
            tempoSRT++;
        }

        // Verifica se a fila e o vetor de processos estão vazios para encerrar o loop
        if (filaPrioridadeSRT.empty() && processosSRT.empty()) {
            executandoSRT = false;
        }
    }

    // Exibe a simulação de uso da CPU para cada tique de relógio
    cout << endl << "Simulação de uso da CPU para cada tique de relógio." << endl << endl;

    for (int i = 0; i < saidaSRT.size(); i++) {
        cout << saidaSRT[i].first << " | ";
    }

    cout << endl;

    for (int i = 0; i < saidaSRT.size(); i++) {
        cout << "-----";
    }

    cout << endl;

    for (int i = 0; i < saidaSRT.size(); i++) {
        if (i > 9) {
            cout << saidaSRT[i].second << "  | ";
        } else {
            cout << saidaSRT[i].second << " | ";
        }
    }
    cout << endl << endl;
}

void RoundRobin() {
    cout << " --------- Algoritmo Round-Robin ----------\n";
    // Lógica Round-Robin

    vector<pair<char, pair<int, int>>> processosRR; // Vetor de processos (nome, (tempo de processamento, tempo de chegada))
    int qtdEntradasRR;

    // Solicita a quantidade de processos a serem inseridos
    do {
        cout << "Quantos processos quer inserir?" << endl;
        cin >> qtdEntradasRR;
        if (qtdEntradasRR > 15) {
            cout << endl << "Você pode inserir no máximo 15 processos!!" << endl << endl;
        }
    } while (qtdEntradasRR > 15);

    processosRR.resize(qtdEntradasRR);

    // Lê os dados dos processos
    for (int i = 0; i < qtdEntradasRR; i++) {
        cout << endl << "Insira o ID do processo, tempo de chegada e tempo de execução:" << endl;
        cin >> processosRR[i].first >> processosRR[i].second.first >> processosRR[i].second.second;
    }

    // Ordena os processos pelo tempo de chegada
    sort(processosRR.begin(), processosRR.end(), ordena);

    // Solicita o valor do quantum
    cout << endl << "Qual será o valor do quantum?" << endl;
    int quantumRR;
    cin >> quantumRR;

    queue<pair<int, char>> filaRR; // Fila de processos (tempo de processamento, nome)
    vector<pair<int, char>> saidaRR; // Vetor para armazenar a sequência de execução dos processos (tempo, nome)
    int tempoRR = 0; // Tempo atual
    bool executandoRR = true; // Flag de controle do loop principal

    while (executandoRR) {
        // Adiciona processos à fila conforme o tempo de chegada
        for (int i = 0; i < processosRR.size();) {
            if (processosRR[i].second.second <= tempoRR) {
                filaRR.push({processosRR[i].second.first, processosRR[i].first});
                processosRR.erase(processosRR.begin() + i);
            } else {
                i++;
            }
        }

        if (!filaRR.empty()) {
            int auxRR = quantumRR;

            // Executa o processo no início da fila pelo tempo do quantum ou até que o processo termine
            while (auxRR-- && filaRR.front().first > 0) {
                filaRR.front().first--; // Decrementa o tempo de processamento do processo atual
                saidaRR.push_back({tempoRR, filaRR.front().second}); // Armazena o tempo atual e o nome do processo
                tempoRR++;

                // Adiciona processos à fila conforme o tempo de chegada
                for (int i = 0; i < processosRR.size();) {
                    if (processosRR[i].second.second <= tempoRR) {
                        filaRR.push({processosRR[i].second.first, processosRR[i].first});
                        processosRR.erase(processosRR.begin() + i);
                    } else {
                        i++;
                    }
                }
            }

            // Se o processo não terminou, move-o para o final da fila
            if (filaRR.front().first > 0) {
                filaRR.push(filaRR.front());
            }
            filaRR.pop(); // Remove o processo da frente da fila
        } else {
            saidaRR.push_back({tempoRR, '*'}); // Armazena o tempo atual e o símbolo ''
            tempoRR++; // Incrementa o tempo se a fila estiver vazia
        }

        // Verifica se a fila e o vetor de processos estão vazios para encerrar o loop
        if (filaRR.empty() && processosRR.empty()) {
            executandoRR = false;
        }
    }

    // Exibe a simulação de uso da CPU para cada tique de relógio
    cout << endl << "Simulação de uso da CPU para cada tique de relógio." << endl << endl;

    for (int i = 0; i < saidaRR.size(); i++) {
        cout << saidaRR[i].first << " | ";
    }

    cout << endl;

    for (int i = 0; i < saidaRR.size(); i++) {
        cout << "-----";
    }

    cout << endl;

    for (int i = 0; i < saidaRR.size(); i++) {
        if (i > 9) {
            cout << saidaRR[i].second << "  | ";
        } else {
            cout << saidaRR[i].second << " | ";
        }
    }
    cout << endl << endl;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int opcao;

    do {
        cout << "-------- TRABALHO SISTEMA OPERACIONAL ---------\n";
        cout << "Escolha uma opção\n";
        cout << "1. Algoritmo SRT\n";
        cout << "2. Algoritmo Round-Robin\n";
        cout << "3. Sair\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                SRT();
                break;
            case 2:
                RoundRobin();
                break;
            case 3:
                cout << "Você saiu do programa!\n";
                break;
            default:
                cout << "Opção invalida!\n";
                break;
        }
    } while (opcao != 3);

    return 0;
}
