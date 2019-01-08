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
        static twitter* instancia(); //Fun��o que retorna o ponteiro para a instancia do twitter
        void cadastro(usuario user); //Cadastro de um usu�rio (recebe um usu�rio)
        bool login(char* login); //Login do usu�rio (recebe o login cadastrado)
        bool seguir(char* nome); //Seguir usu�rio (recebe o login a ser seguido)
        bool enviartwitter(char* mens); //Manda um tu�te para o arquivo e coloca seu ID como chave da �rvore
        bool procurarmensagemeretwitter(char *mens); //Busca de mensagens pelo shift-end
        bool retwittar(); //Retuita uma mensagem com o usu�rio logado
        bool enviarretwitter(mensagem ret);
        bool exibeperfilusuario(int i); //Exibe perfil de um usu�rio existente de ID i
        bool procuraperfilusuario(char *nome); //Procura usu�rio de ID i. Caso encontrado, retorna verdadeiro
        bool feed(); //Exibe a mensagen mais recente de cada usu�rio seguido pelo usu�rio logado
        void armazenausuario(); //Armazena o usu�rio no arquivo bin�rio
        void recebeusuario(); //Recebe um usu�rio do arquivo
        string convertInt(int); //Converte int para string
};

#endif // TWITTER_H_INCLUDED
