#include "twitter.h"


twitter::twitter() {}

string twitter::convertInt(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0; i<temp.length(); i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void twitter::cadastro(usuario user)
{
    listaUser.push_back(user);
}

bool twitter::feed()
{
    ifstream is("arquivo.bin",ios::binary);
    map <string,int> aux = listaUser[usuariologado].retornafeed();
    map<string, int>::iterator it;
    for (it = aux.begin(); it != aux.end(); ++it)
    {
        //cout << "\nusuario X: " << listaUser[it->second].getnome() << endl;
        map <int, int> auxMsg = listaUser[it->second].getmensusuario();
        map<int, int>::iterator it2;
        map<int, int>::reverse_iterator itR;
        if (!auxMsg.empty())
        {
            itR = auxMsg.rbegin();
            cout <<listaUser[it->second].getnome()<< "   :";
            mensagem aux3(is,itR->second);
            cout << aux3.getconteudo() <<endl;
        }
    }
    is.close();
}

bool twitter::login(char* login)
{
    for(int i=0; i<GeradorDeIDuser ; i++)
    {
        if (strcmp(listaUser[i].getlogin(), login) == 0)
        {
            usuariologado = listaUser[i].getid();
            return true;
        }
    }
    return false;
}

bool twitter::seguir(char* nome)
{
    for(int i=0; i<GeradorDeIDuser ; i++)
    {
        if (strcmp(listaUser[i].getlogin(), nome) == 0)
        {
            listaUser[i].setseguidores();
            listaUser[usuariologado].setseguindo(nome, i);

            return true;
        }
    }
    return false;
}

bool twitter::exibeperfilusuario(int i)
{
    ifstream is("arquivo.bin",ios::binary);
    map<int,int>aux = listaUser[i].getmensusuario();
    cout<<"\nNome :"<<listaUser[i].getnome()<<" | Seguidores:"<<listaUser[i].getseguidores()<<" |  Seguindo:"<<listaUser[i].getseguindo()<<endl;
    map<int, int>::iterator it;
    cout<<"mensagens: \n";
    for (it = aux.begin(); it != aux.end(); ++it)
    {
        mensagem aux3(is,it->second);
        cout << aux3.getconteudo() <<endl;
    }
}


bool twitter::procuraperfilusuario(char *nome)
{

    for(int i=0; i<GeradorDeIDuser ; i++)
    {
        if (strcmp(listaUser[i].getnome(), nome) == 0)
        {
            exibeperfilusuario(i);
            return true;
        }
    }
    return false;
}

bool twitter::enviartwitter(char *mens)
{
    mensagem aux;
    aux.setidUser(usuariologado);
    aux.setconteudo(mens);
    aux.setid(GeradorDeIDMensagem);
    listaUser[usuariologado].setmensusuario(GeradorDeIDMensagem);
    GeradorDeIDMensagem++;
    bt.put(aux.getid(),aux.getid());
    cout<<usuariologado;
    mensagem::armazenabin(aux);
}

bool twitter::retwittar()
{
    char e;
    cout<<"\nDeseja retwittar essa mensagem(s para sim)\n";
    cin>>e;
    if(e='s')return true;
    else return false;
}


bool twitter::procurarmensagemeretwitter(char *mens)
{

    ifstream is("arquivo.bin",ios::binary);
    int aux;
    int aux2;
    if((GeradorDeIDMensagem<10))aux=0;
    else aux=GeradorDeIDMensagem-10;
    aux2=GeradorDeIDMensagem;
    map<int, int> res = bt.getrange(aux,aux2-2);
    bt.get(GeradorDeIDMensagem-1,aux2);
    res[GeradorDeIDMensagem-1]=aux2;
    map<int, int>::iterator it;

    for (it = res.begin(); it != res.end(); ++it)
    {
        unsigned long long ab[256] = {0}, estado = 0;
        int tam=0, i, j;
        char padrao[140];
        strcpy(padrao,mens);
        mensagem aux3(is,it->second);
        string texto = aux3.getconteudo();

        while(padrao[tam++]!='\0');
        tam--;
        for (int i = tam-1, j=0; i>=0; i--,j++)
        {
            ab[padrao[i]] |= (1<<j);
        }
        estado =0;
        for(i=0; i<texto.size(); i++)
        {
            estado = ((1 <<(tam-1)) | (estado>>1)) & (ab[texto[i]]);
            if (estado &1)
            {

                cout <<endl<<"Termo encontrado na mensagem:"<<endl<< aux3.getconteudo() << "\n";
                cout <<"| Mensagem enviada por: "<< listaUser[aux3.getidUser()].getnome();
                if(retwittar())
                {
                    enviartwitter(aux3.getconteudo());
                }
                break;
            }

        }
    }
    is.close();
}


twitter* twitter::ptrInstancia = NULL;

twitter* twitter::instancia()
{
    if (ptrInstancia == 0) ptrInstancia = new twitter();
    return ptrInstancia;
}

void twitter::recebeusuario()
{
    for(int i=0; i<GeradorDeIDuser; i++)
    {
        string converte = convertInt(i);
        ifstream fs2((converte + "Feed"), ios::binary);
        usuario aux(fs2);
        fs2.close();
        ifstream fs3((converte + "Msg"), ios::binary);
        aux.pegamens(fs3);
        fs3.close();
        listaUser.push_back(aux);
    }
}

void twitter::armazenausuario()
{
    for(int i=0; i<GeradorDeIDuser; i++)
    {
        usuario::armazenaMsg(listaUser[i]);
        usuario::armazenaFeed(listaUser[i]);
    }

}
