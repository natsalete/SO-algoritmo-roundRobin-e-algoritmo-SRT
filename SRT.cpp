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
    cout << "Algoritmo Shortest Remaining Time (SRT)!" << endl << endl;

    vector<pair<char, pair<int, int>>> v; // Vetor de processos (nome, (tempo de processamento, tempo de chegada))
    int qtdEntradas;

    // Solicita a quantidade de processos a serem inseridos
    do{
        cout << "Quantos processos quer inserir?" << endl;
        cin >> qtdEntradas;
        if(qtdEntradas > 15){
            cout << endl << "Vc pode inserir no maximo 15 processos!!" << endl << endl;
        }
    }while(qtdEntradas > 15 || qtdEntradas <= 0);

    v.resize(qtdEntradas);

    // Lê os dados dos processos
    for (int i = 0; i < qtdEntradas; i++) {
        cout << endl << "Insira o ID do processo(caracter), tempo de processamento e tempo de chegada:" << endl;
        cin >> v[i].first >> v[i].second.first >> v[i].second.second;
    }

    // Ordena os processos pelo tempo de chegada
    sort(v.begin(), v.end(), ordena);

    // Fila de prioridade para processos (tempo de processamento restante, tempo de chegada, nome do processo)
    priority_queue<pair<int, pair<int, char>>, vector<pair<int, pair<int, char>>>, greater<pair<int, pair<int, char>>>> pq;
    vector<pair<int, char>> vSaida; // Vetor para armazenar a sequência de execução dos processos (tempo, nome)
    int tempo = 0; // Tempo atual
    bool ok = true; // Flag de controle do loop principal

    while (ok) {
        // Adiciona processos à fila de prioridade conforme o tempo de chegada
        for (int i = 0; i < v.size();) {
            if (v[i].second.second <= tempo) {
                pq.push({v[i].second.first, {v[i].second.second, v[i].first}});
                v.erase(v.begin() + i);
            } else {
                i++;
            }
        }

        if (!pq.empty()) {
            auto processoAtual = pq.top();
            pq.pop();

            // Executa o processo com o menor tempo restante por um tique de relógio
            vSaida.push_back({tempo, processoAtual.second.second}); // Armazena o tempo atual e o nome do processo
            tempo++;

            // Reduz o tempo restante do processo em 1
            processoAtual.first--;

            // Se o processo ainda não terminou, coloca-o de volta na fila de prioridade
            if (processoAtual.first > 0) {
                pq.push(processoAtual);
            }
        } else {
            // Se não há processos prontos, incrementa o tempo sem executar nada
            vSaida.push_back({tempo, '*'});
            tempo++;
        }

        // Verifica se a fila e o vetor de processos estão vazios para encerrar o loop
        if (pq.empty() && v.empty()) {
            ok = false;
        }
    }

    // Exibe a simulação de uso da CPU para cada tique de relógio
    cout << endl << "Simulação de uso da CPU para cada tique de relógio." << endl << endl;

    for (int i = 0; i < vSaida.size(); i++) {
        cout << vSaida[i].first << " | ";
    }

    cout << endl;

    for (int i = 0; i < vSaida.size(); i++) {
        cout << "-----";
    }

    cout << endl;

    for (int i = 0; i < vSaida.size(); i++) {
        if (i > 9) {
            cout << vSaida[i].second << "  | ";
        } else {
            cout << vSaida[i].second << " | ";
        }
    }

    return 0;
}


