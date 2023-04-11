#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Lucas Teixeira Soares - 32124831

Nessa implementação decidimos fazer uma
implementação recursiva de um AFND, que utiliza
backtracking.
*/

// O nome do arquivo de texto precisa ser texto.txt

/*
Essa função é a que faz a recursividade com backtracking.
Primeiro ela checa se está no final da palavra, se sim ela
checa se está em um dos estados finais, se sim ela retorna true
se não ela retorna false. Se não está no final
da palavra ela checa a matriz de transições para ver se existe
uma transição possivel, se sim ela chama recursividade aumentando
o i e trocando o estado_atual, e se essa chamada recursiva retornar
true ela retorna true caso ela retornar false ela continua checando
os transições para ver se existe outra possivel e se acabarem 
todas as transcições ela apenas retorna false.
*/
bool teste_recursivo(char estado_atual, int i, char* palavra, int qntTrans, char* estadosFinais, int qntEstadosFinais, char matriz_transicoes[100][3]){
  if(palavra[i] == '\n'){
    for(int j = 0; j < qntEstadosFinais; j++){
      if(estado_atual == estadosFinais[j])
        return true;
    }
    return false;
  }

  for(int j = 0; j < qntTrans; j++){
    if(estado_atual == matriz_transicoes[j][0]){
      if(palavra[i] == matriz_transicoes[j][1]){
        if(teste_recursivo(matriz_transicoes[j][2], (i+1), palavra, qntTrans, estadosFinais, qntEstadosFinais, matriz_transicoes) == true)
          return true;
        else
          continue;
      }
    }
  }
  
  return false;
}

// esa função é inicializadora da teste_recursivo
bool teste_palvra(char *palavra, int qntTrans, char* estadosFinais, int qntEstadosFinais, char matriz_transicoes[100][3]) {
  return teste_recursivo('0', 0, palavra, qntTrans, estadosFinais, qntEstadosFinais, matriz_transicoes);
}

int main(void) {

  char alfabeto[11], qntEstados_string[5], qntEstadosFinais_string[5], estadosFinais[21],
      qntTrans_string[5], transicoes[7], testes[30], matriz_transicoes[100][3], *string;
  int i, tamanhoAlfabeto;
  FILE *arq = fopen("texto.txt", "r");
  
  if(arq == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }
  
  string = fgets(alfabeto, sizeof alfabeto, arq);        //armazena alfabeto
  string = fgets(qntEstados_string, sizeof qntEstados_string, arq);              //armazena qtd de estados
  string = fgets(qntEstadosFinais_string, sizeof qntEstadosFinais_string, arq); //armazena qtd de estados finais
  string = fgets(estadosFinais, sizeof estadosFinais, arq);  //armazena estados finais
  string = fgets(qntTrans_string, sizeof qntTrans_string, arq);    //armazena qtd de transicoes
  

  // convertendo números importantes em int
  int qntEstados = atoi(qntEstados_string);
  int qntEstadosFinais = atoi(qntEstadosFinais_string);
  int qntTrans = atoi(qntTrans_string);

  printf("\nAlfabeto: %s", alfabeto);
  printf("\nQuantidade de estados: %d\n", qntEstados);
  printf("\nQuantidade de estados finais: %d\n", qntEstadosFinais);
  printf("\nNumero de transições: %d\n", qntTrans);
  
  printf("\nEstados: ");
  for (i = 0; i < qntEstados; i++) {
    printf("{Q%d} ", i);
  }


  
  printf("\n\nEstado(s) Final(is):");

  if(qntEstadosFinais == 1)
    printf("{Q%c} ", estadosFinais[0]);
  else{
    // (tamanhoEF*2)-1 para levar em conta os ' ' na linha
    for(i = 0; i < (qntEstadosFinais*2)-1; i++){
      if(estadosFinais[i] == ' ')
        continue;
      printf("{Q%c} ", estadosFinais[i]);
    }
  }

  int linha, j = 0;
  
  printf("\n\nTransições: \n");
  
  for (i = 0; i < qntTrans; i++) {
    char *c = fgets(transicoes, sizeof transicoes, arq);
    linha = 0;

    // denovo fazendo uma gambiara para evitar os ' ' da linha
    for(j = 0; j < 5; j++){
      if(transicoes[j] == ' ')
        continue;

      matriz_transicoes[i][linha] = transicoes[j];
      linha++;
    }
    
    printf("%s", c);
  }

  string = fgets(testes, sizeof testes, arq);
  int qntTestes = atoi(testes);
  int caracter;
  printf("\nQuantidade de teste(s): %d.\n", qntTestes);
  printf("\nTestes: \n");
  
  // a medida que os testes são lidos eles já são testados.
  while (!feof(arq)) {
    string = fgets(testes, sizeof testes, arq);
    
    // pequena gambiara para evitar o '\n' para o print.
    caracter = 0;
    while(string[caracter] != '\n'){
      printf("%c", string[caracter]);
      caracter++;
    }
    
    printf(" - %s \n", teste_palvra(testes, qntTrans, estadosFinais, qntEstadosFinais, matriz_transicoes) ? "true" : "false");
  }
  printf("\n");
  
  fclose(arq);

  
  
  return 0;
}