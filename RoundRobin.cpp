#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Função de comparação para ordenar os processos pelo tempo de chegada
bool ordena(pair<char, pair<int, int>> a, pair<char, pair<int, int>> b) {
    return a.second.second < b.second.second;
}

int main() {

    cout << "Algoritmo round-Robin!" << endl << endl;

    vector<pair<char, pair<int, int>>> v; // Vetor de processos (nome, (tempo de processamento, tempo de chegada))
    int qtdEntradas;

    // Solicita a quantidade de processos a serem inseridos
    cout << "Quantos processos quer inserir?" << endl;
    cin >> qtdEntradas;

    v.resize(qtdEntradas);

    // Lê os dados dos processos
    for (int i = 0; i < qtdEntradas; i++) {
        cout << endl << "Insira o ID do processo, tempo de chegada e tempo de execucao:" << endl;
        cin >> v[i].first >> v[i].second.first >> v[i].second.second;
    }

    // Ordena os processos pelo tempo de chegada
    sort(v.begin(), v.end(), ordena);

    // Solicita o valor do quantum
    cout << endl << "Qual sera o valor do quantum?" << endl;
    int quantum;
    cin >> quantum;

    // Exibe os dados dos processos inseridos para verificação
    /*for (const auto& entrada : v) {
        cout << "Processo: " << entrada.first << ", Tempo Processamento: " << entrada.second.first << ", Tempo Chegada: " << entrada.second.second << endl;
    }*/

    queue<pair<int, char>> fila; // Fila de processos (tempo de processamento, nome)
    vector<pair<int, char>> vSaida; // Vetor para armazenar a sequência de execução dos processos (tempo, nome)
    int tempo = 0; // Tempo atual
    bool ok = true; // Flag de controle do loop principal

    while (ok) {
        // Adiciona processos à fila conforme o tempo de chegada
        for (int i = 0; i < v.size();) {
            if (v[i].second.second <= tempo) {
                fila.push({v[i].second.first, v[i].first});
                v.erase(v.begin() + i);
            } else {
                i++;
            }
        }

        if (!fila.empty()) {
            int aux = quantum;

            // Executa o processo no início da fila pelo tempo do quantum ou até que o processo termine
            while (aux-- && fila.front().first > 0) {
                fila.front().first--; // Decrementa o tempo de processamento do processo atual
                vSaida.push_back({tempo, fila.front().second}); // Armazena o tempo atual e o nome do processo
                tempo++;

                // Adiciona processos à fila conforme o tempo de chegada
                for (int i = 0; i < v.size();) {
                    if (v[i].second.second <= tempo) {
                        fila.push({v[i].second.first, v[i].first});
                        v.erase(v.begin() + i);
                    } else {
                        i++;
                    }
                }
            }

            // Se o processo não terminou, move-o para o final da fila
            if (fila.front().first > 0) {
                fila.push(fila.front());
            }
            fila.pop(); // Remove o processo da frente da fila
        } else {
            tempo++; // Incrementa o tempo se a fila estiver vazia
        }

        // Verifica se a fila e o vetor de processos estão vazios para encerrar o loop
        if (fila.empty() && v.empty()) {
            ok = false;
        }
    }

    // Exibe a simulação de uso da CPU para cada tique de relógio
    cout << endl << "Simulacao de uso da CPU para cada tique de relogio." << endl << endl;

    for (int i = 0; i < vSaida.size(); i++) {
        cout << vSaida[i].first << " | ";
    }

    cout << endl << "------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < vSaida.size(); i++) {
        cout << vSaida[i].second << " | ";
    }

    return 0;
}
