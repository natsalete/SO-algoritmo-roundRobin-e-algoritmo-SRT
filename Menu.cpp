#include <iostream>
#include <locale>
using namespace std;
void SRT() {

    cout << "Algoritmo SRT\n";
    // L�gica SRT
}

void RoundRobin() {

    cout << "Algoritmo Round-Robin\n";
    // L�gica Round-Robin
}
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int opcao;

    do {
        cout << "-------- Menu ---------\n";
        cout << "Escolha uma op��o:\n";
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
                cout << "Voc� saiu do programa\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 3);

    return 0;
}
