#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Contato {
private:
    string name;
    map<string, int> telefones;
    int contCall;

public:
    Contato(string name) {
        this->name = name;
        contCall = 0;
    }

    string getName() const {
        return this->name;
    }

    int getContCall() const {
        return this->contCall;
    }

    void incContCalll() {
        contCall++;
    }

    void addTelefone(string telefone) {
        telefones[telefone] = 0;
    }

    void removeTelefone(string telefone) {
        telefones.erase(telefone);
    }

    bool possuiTelefone(string telefone) const {
        return telefones.count(telefone) > 0;
    }

    void incContCallTelefone(string telefone) {
        telefones[telefone]++;
    }

    friend ostream& operator<<(ostream& os, const Contato& contato) {
        os << contato.name << " (" << contato.contCall << ")";
        return os;
    }
};

class SpeedList {
private:
    vector<Contato*> contatos;

public:
    void addContact(Contato* contato) {
        contatos.push_back(contato);
    }

    void removerContato(Contato* contato) {
        contatos.erase(remove(contatos.begin(), contatos.end(), contato), contatos.end());
    }

    void mostrarSpeedList() const {
        vector<Contato*> speedList(contatos);
        sort(speedList.begin(), speedList.end(), [](const Contato* a, const Contato* b) {
            if (a->getContCall() != b->getContCall()) {
                return a->getContCall() > b->getContCall();
            } else {
                return a->getName() < b->getName();
            }
        });

        for (const auto& contato : speedList) {
            cout << *contato << endl;
        }
    }
};

// class Historico {
// private:
//     vector<pair<string, int>> ligacoes;

// public:
//     void adicionarLigacao(string numero) {
//         bool encontrado = false;

//         for (auto& ligacao : ligacoes) {
//             if (ligacao.first == numero) {
//                 ligacao.second++;
//                 encontrado = true;
//                 break;
//             }
//         }

//         if (!encontrado) {
//             ligacoes.push_back(make_pair(numero, 1));
//         }
//     }

//     void mostrarHistorico(const vector<Contato*>& contatos) const {
//         for (const auto& ligacao : ligacoes) {
//             string numero = ligacao.first;
//             int contCall = ligacao.second;
//             bool encontrado = false;

//             for (const auto& contato : contatos) {
//                 if (contato->possuiTelefone(numero)) {
//                     cout << *contato << ": " << numero << " (" << contCall << ")" << endl;
//                     encontrado = true;
//                     break;
//                 }
//             }

//             if (!encontrado) {
//                 cout << numero << " (" << contCall << ")" << endl;
//             }
//         }
//     }
// };

class Agenda :public SpeedList{
private:
    vector<Contato*> contatos;
    SpeedList speedList;
    // Historico historico;

    Contato* findContactForName(const string& name) const {
        for (const auto& contato : contatos) {
            if (contato->getName() == name) {
                return contato;
            }
        }
        throw "Contato nao encontrado";
        return nullptr;
    }

    Contato* findContactForTelefone(const string& telefone) const {
        for (const auto& contato : contatos) {
            if (contato->possuiTelefone(telefone)) {
                return contato;
            }
        }
        return nullptr;
    }

public:
    Agenda() {
        for (const auto& contato : contatos) {
            delete contato;
        }
    }

    void addContact(const string& name) {
        
        if (findContactForName(name) == nullptr) {
            Contato* newContact = new Contato(name);
            contatos.push_back(newContact);
            speedList.addContact(newContact);
        }
        throw "Contato ja existe";
    }

    // void removerContato(const string& name) {
    //     Contato* contato = findContactForName(name);
    //     if (contato != nullptr) {
    //         contatos.erase(remove(contatos.begin(), contatos.end(), contato), contatos.end());
    //         speedList.removerContato(contato);
    //         delete contato;
    //     }
    // }

    void addTelefone(const string& name, const string& telefone) {
        Contato* contato = findContactForName(name);
        if (contato != nullptr) {
            contato->addTelefone(telefone);
        }
    }

    // void removeTelefone(const string& telefone) {
    //     Contato* contato = findContactForTelefone(telefone);
    //     if (contato != nullptr) {
    //         contato->removeTelefone(telefone);
    //     }
    // }

    // void ligar(const string& numero) {
    //     Contato* contato = findContactForTelefone(numero);
    //     if (contato != nullptr) {
    //         contato->incContCallTelefone(numero);
    //         contato->incContCalll();
    //         historico.adicionarLigacao(numero);
    //     } else {
    //         Contato* newContact = new Contato(numero);
    //         newContact->incContCallTelefone(numero);
    //         newContact->incContCalll();
    //         contatos.push_back(newContact);
    //         speedList.addContact(newContact);
    //         historico.adicionarLigacao(numero);
    //     }
    // }

    // void ligar(const string& nameContato) {
    //     Contato* contato = findContactForName(nameContato);
    //     if (contato != nullptr && !contato->getName().empty()) {
    //         const auto& telefones = contato->telefones;
    //         if (!telefones.empty()) {
    //             const string& primeiroTelefone = telefones.begin()->first;
    //             contato->incContCallTelefone(primeiroTelefone);
    //             contato->incContCalll();
    //             historico.adicionarLigacao(primeiroTelefone);
    //         }
    //     }
    // }

    // void mostrarSpeedList() const {
    //     speedList.mostrarSpeedList();
    // }

    // void mostrarHistorico() const {
    //     historico.mostrarHistorico(contatos);
    // }
};

int main() {
    Agenda agenda;
    try {
        cout << "$ add João" << endl;
        agenda.addContact("João");
        cout << "$ add Maria" << endl;
        agenda.addContact("Maria");
        cout << "$ add Pedro" << endl;
        agenda.addContact("Pedro");
    } catch ( const std::exception& e) {
        cout << e.what() << endl;
    }
    // cout << "$ phone João 12345" << endl;
    // agenda.addTelefone("João", "12345");
    // cout << "$ phone João 67890" << endl;
    // agenda.addTelefone("João", "67890");
    // cout << "$ phone Maria 54321" << endl;
    // agenda.addTelefone("Maria", "54321");
    // cout << "$ phone Pedro 98765" << endl;
    // agenda.addTelefone("Pedro", "98765");
    // cout << "$ list" << endl;
    // agenda.mostrarSpeedList();
    // cout << "$ call 12345" << endl;
    // agenda.ligar("12345");
    // cout << "$ call 54321" << endl;
    // agenda.ligar("54321");
    // cout << "$ call Maria" << endl;
    // agenda.ligar("Maria");
    // cout << "$ call 67890" << endl;
    // agenda.ligar("67890");
    // cout << "$ call 98765" << endl;
    // agenda.ligar("98765");
    // cout << "$ history" << endl;
    // agenda.mostrarHistorico();

    return 0;
}