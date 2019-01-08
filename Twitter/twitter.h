#ifndef TWITTER_H_INCLUDED
#define TWITTER_H_INCLUDED
#include <vector>
#include "usuario.h"
#include "BPlusTree.hpp"
#include <map>
#include "mensagem.h"

class twitter{
    private:
    vector<usuario> listaUser;
    int usuariologado;
    BPlusTree bt;
    static twitter *ptrInstancia;
    twitter();
    public:
        static twitter* instancia(); //Função que retorna o ponteiro para a instancia do twitter
        void cadastro(usuario user); //Cadastro de um usuário (recebe um usuário)
        bool login(char* login); //Login do usuário (recebe o login cadastrado)
        bool seguir(char* nome); //Seguir usuário (recebe o login a ser seguido)
        bool enviartwitter(char* mens); //Manda um tuíte para o arquivo e coloca seu ID como chave da árvore
        bool procurarmensagemeretwitter(char *mens); //Busca de mensagens pelo shift-end
        bool retwittar(); //Retuita uma mensagem com o usuário logado
        bool enviarretwitter(mensagem ret);
        bool exibeperfilusuario(int i); //Exibe perfil de um usuário existente de ID i
        bool procuraperfilusuario(char *nome); //Procura usuário de ID i. Caso encontrado, retorna verdadeiro
        bool feed(); //Exibe a mensagen mais recente de cada usuário seguido pelo usuário logado
        void armazenausuario(); //Armazena o usuário no arquivo binário
        void recebeusuario(); //Recebe um usuário do arquivo
        string convertInt(int); //Converte int para string
};

#endif // TWITTER_H_INCLUDED
