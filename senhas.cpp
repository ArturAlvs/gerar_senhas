#include <iostream>
#include <math.h>

const char *alphabet =  "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "0123456789";

int alphaLen = strlen(alphabet);
using namespace std;
void geraSenha(unsigned long iteracao,  int tam_senha, char* senha){
     
    for(int x = 0; x < tam_senha + 1; x++){
        senha[x] = 'a';
    }
    senha[tam_senha] = '\0';
    int indice = tam_senha - 1;

    int d, r;

    do{
        d = iteracao / alphaLen;
        r = iteracao % alphaLen;

        senha[indice] = alphabet[r];
        indice--;
        iteracao = d;
    }
    while(iteracao != 0);

    cout << senha << endl;
}


int main(int argc, char *argv[]){

    int tam_senha = atoi(argv[1]);
    int qtd_threads = 10;

    unsigned long  iteracao_max = pow(alphaLen, tam_senha);

    char **senhas_thread = (char**) malloc(sizeof(char*) * qtd_threads);
    for(int i = 0; i < qtd_threads; i++){
        senhas_thread[i] = (char*) malloc(sizeof(char) * (tam_senha +1) );
        senhas_thread[i][tam_senha] = '\0';
    }

    unsigned long letra_ce_q = 0;

    int sair = 1;

    cout << "Qual letra ce quer? (min: 0, max:" << iteracao_max << ")" << endl;

	cin >> letra_ce_q;

    while(sair)
    {

    	if (letra_ce_q < (qtd_threads/2) || letra_ce_q > (iteracao_max - (qtd_threads/2)))
    	{
    		cout << "Adeus! :)" << endl;
    		exit(0);
    	}
    
	    for(unsigned long i = (letra_ce_q - (qtd_threads/2)); i < (letra_ce_q + (qtd_threads/2)); i++){
	        geraSenha(i,tam_senha, senhas_thread[0]);  
	    }

	    char acao;
	    cout << "v,g,s ?" << endl;
	    cin >> acao;

	    if (acao == 'v')
	    {
	    	letra_ce_q += qtd_threads;
	    }
	    else if (acao == 'g')
	    {
	    	letra_ce_q -= qtd_threads;	
	    }
	    else if (acao == 's')
	    {
	    	cout << "Adeus! :(" << endl;
    		exit(0);	
	    }
    }
    return 0;
}
