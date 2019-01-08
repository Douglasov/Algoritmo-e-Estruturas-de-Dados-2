#include <iostream>
using namespace std;

int main()
{
    //abre texto.txt
    unsigned long long ab[256] = {0}, estado = 0;
    char padrao[65];
    cin >> padrao;
    for (int i = 0; padrao[i] != '\0'; i++)
    {
        ab[padrao [i]] |= (1<<i);
    }
    while (/*enquanto nao chegou no fim do arquivo*/)
    {
        estado |= (1<<(/*tamanho do padrao menos 1*/)) | (ab[texto[i++]] & estado);
        if (estado &1) cout << "true";
        estado >>= 1;
    }
    return 0;
}
