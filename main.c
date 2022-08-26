#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define limpaTela() system("clear")
#define linhaP 23 //linha da matriz de perguntas
#define colunaP 150 //coluna da matriz de perguntas
#define rodadas 10 //quantidade de perguntas para responder

int primeiroIniciar = 0;

char decisao;
int qtdJogadores;

char perguntas[linhaP][colunaP] = {
  "O panda-vermelho nativo do himalaia deu origem ao nome do navegador Firefox.", 
  "MacBooks são imunes a vírus.", 
  "A Apple inventou o tablet.", 
  "A origem da palavra *robô* remete a trabalho técnico.",
  "Um disco rígido de 5 MB pesava uma tonelada em 1956.",
  "O e-mail foi criado antes da internet.",
  "A sigla *www* significa *World Wide Web*.",
  "A duração do primeiro vídeo do YouTube foi de 18 segundos.", 
  "A primeira rede social da história da internet foi o Orkut.",
  "Em um byte cabem 8 bits.",
  "Em 2000 foi criado o primeiro smartphone da história.",
  "A inteligencia artificial funciona da mesma maneira que o cérebro humano.",
  "Um processador octa-core tem 8 núcleos.",
  "É possível receber dinheiro de volta fazendo compras em e-commerce.",
  "A sigla LGPD significa *Lei Geral de Proteção de Dados*.",
  "Os aplicativos de mensagens não usam criptografia de ponta a ponta.",
  "Brinquedos também podem ter funções de conectividade e acesso à internet.",
  "O nome do navegador da Macrosoft é Google Chrome.",
  "Em Machine Learning as maquinas aprendem sozinhas analisando dados e detectando padrões.",
  "Big Data é uma linguagem de programação.",
  "A porta USB serve para conectar periféricos que podem transmitir e armazenar dados.",
  "Na Computação em Nuvem os arquivos, aplicativos e sistemas podem ser acessados de qualquer lugar do mundo.",
  "Reconhecimento Facial identifica pessoas usando biometria facial, mesmo que estejam em meio a uma multidão."
};

char respostas[linhaP][1] = {
  "v",
  "f",
  "f",
  "f",
  "v",
  "v",
  "v",
  "v",
  "f",
  "v",
  "f",
  "f",
  "v",
  "v",
  "v",
  "f",
  "v",
  "f",
  "v",
  "f",
  "v",
  "v",
  "v"
};

void menu() {
  srand((unsigned)time(NULL)); //seed aleatoria

  if(primeiroIniciar == 0){
    limpaTela();
    printf("Bem vindo(a) ao nosso quiz sobre...\n");
    primeiroIniciar = 1;
  }
  printf("\n------------- TECNOLOGIA -------------\n\n");

  while(1){
    printf("Digite:\n");
    printf("[1] Para iniciar o jogo\n[0] Para sair do jogo\nEscolha: ");
    scanf(" %c", &decisao);

    if (decisao != '1' && decisao != '0') {
      limpaTela();
      printf("\nEscolha invalida. Por favor, escolha uma das opções abaixo.\n");
    }else{
      break;
    }
  }

  if (decisao == '1') {
    while(1) {
      while(getchar() != '\n');
      printf("\nQuantos jogadores irão participar? ");
      scanf("%d", &qtdJogadores);

      if(qtdJogadores > 10) {
          printf("\nO limite de jogadores é 10, informe um valor válido.\n");
          while(getchar() != '\n'); //Esvazia buffer
      }else if(qtdJogadores <= 0) {
          printf("\nO numero de jogadores não pode ser menor ou igual a 0.\n"); 
          while(getchar() != '\n'); //Esvazia buffer
      }else{
          limpaTela();
          break;
      }
    }
  }
}

// Embaralhas lista 1D
void shuffle1D(int *array, int n) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

// Embaralhar lista 2D para perguntas/respostas
void shuffle2D(int colunas, char lista[linhaP][colunas]) {

    int posicao[linhaP];
    char auxiliar[linhaP][colunas];

    for(int i=0; i<linhaP; i++){
      posicao[i] = i;
    }

    shuffle1D(posicao, linhaP); //Aleatoriza posições

    //Insere pergunta/resposta em posição aleatoria já definida na variavel auxiliar
    for(int i = 0; i < linhaP; i++){
      strncpy(auxiliar[i], lista[posicao[i]], colunas);
    }
    //Insere dados auxiliares nas variaveis normais
    for(int i = 0; i < linhaP; i++){
      strncpy(lista[i], auxiliar[i], colunas);
    }
}

//imprimir a pontuação de cada participante
void printPontuacao(int pontosJogador[]){
  int maior = 0, empatou = -1, vencedor, empate[qtdJogadores];
  printf("\n========== [ RANKING ] ==========\n\n");

  for(int i = 0; i < qtdJogadores; i++){
    printf("Jogador[%d] = %d\n", i+1, pontosJogador[i]);
    //verificando maior potuanção.
    if(pontosJogador[i] > maior){
      maior = pontosJogador[i];
      vencedor=i+1;
    }
  }

  for(int i = 0; i < qtdJogadores; i++){
    //verificar empates
    if(pontosJogador[i] == maior){
      if(empatou >= 1){
        empate[i] = i+1;
      }else{
        empate[i] = i+1;
        empatou++;
      }
    }
  }

  if(empatou >= 1){
    printf("\n** Empate entre os jogadores // Pontuação = %d **\n\n", maior);
    for(int i=0; i<qtdJogadores+1; i++){
      if(empate[i] >= 1){
        printf("/ Jogador[%d] ", empate[i]);
      }
    }printf("/\n");
  }else if(qtdJogadores <= 1){
    printf("\n** Você terminou o quiz com %d pontos! **\n\n", maior);
  }else{
  printf("\n** O grande vencedor é o Jogador[%d] com %d pontos! **\n\n", vencedor, maior);
  }

  printf("Retornando ao menu principal...\n");
}

//zerar a contagem de pontos
int *resetPontuacao(int jogadores[]){
   int i;
   for ( i = 0; i < qtdJogadores; i++) {
      jogadores[i] = 0;
   }
   return jogadores;
}

//Criação do Quiz
void setupQuiz(){
  //Contagem regressiva
  shuffle2D(colunaP, perguntas);
  shuffle2D(1, respostas);
  //shuffle2D(1, respostas);
  printf("Começando o Quiz em...\n"); 
  int contRegressiva, l, c;
  for(contRegressiva = 3; contRegressiva > 0 ; contRegressiva--){
    printf("%d...\n",contRegressiva);
    sleep(1);
  }

  //resposta do usuário
  char res[linhaP];

  printf("\n* Digite [V] para verdadeiro e [F] para falso *\n");
 
  //usando apontadores para zerar o array da pontuação
  //shuffle(perguntas, linhaP, colunaP);
  int jogs[qtdJogadores];
  int *pJogadores;
  pJogadores = resetPontuacao(jogs);
  

  for(l=0; l<rodadas; l++){
    printf("\n-----------( RODADA %d )-----------\n",l+1);
    //Contagem de rodadas onde cada participante responde uma questão
    for(c=0; c < colunaP; c++){
      printf("%c",perguntas[l][c]);
    }
    printf("\n");
    
    for(int j=0; j<qtdJogadores; j++){
      printf("\n[Jogador %d]\n", j+1);
      
      printf("* Resposta: ");
      while(getchar() != '\n' );
      scanf("%c", &res[l]);
      res[l] = tolower(res[l]);
      //printf("\nlower fora %c\n", res[l]);

      while(res[l] != 'v' &&  res[l] != 'f'){
        while(getchar() != '\n' ); // Esvazia buffer
        printf("[Opção inválida]\n* Resposta: ");
        scanf("%c", &res[l]);
        res[l] = tolower(res[l]);
        //printf("\nlower  dentro %c\n", res[l]);
      }

      //somar pontos do/s participante/s
      if(res[l] == respostas[l][0]){
        pJogadores[j] +=1;
      }
    }
  }
  //Imprimir pontuações
  printPontuacao(pJogadores);
}


int main(void){
    do {
        //limpaTela();
        menu();

        if (decisao == '0') {
            break;
        }

        // O codigo do quiz vai vir aqui
        printf("\n%d Jogador(es) participando.\n\n", qtdJogadores);
        setupQuiz();
        
        //sleep(3);
        
    } while(decisao != '0');

    printf("\nObrigado por jogar!\n");

    return 0;
}