#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 100
#define NUM_LETRAS 26
#define ASCII_A 65
#define TAMANHO_SENHA 4

// Estrutura para passar múltiplos argumentos para as threads
typedef struct {
  char *arquivo; // Nome do arquivo a ser processado
  int indice; // Índice do arquivo, usado para gerar o nome do arquivo de saída
} ThreadArgs;

// Função que realiza a criptografia de uma string
char *encrypt(const char *str) {
  char *str_result = (char *)malloc(sizeof(char) * (TAMANHO_SENHA + 1));
  if (!str_result) {
    perror("Erro ao alocar memoria");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < TAMANHO_SENHA; i++) {
    char c = str[i];
    char chave = str[i];

    if (c >= 'A' && c <= 'Z') {
      int str_idx = c - ASCII_A;
      int chave_idx = chave - ASCII_A;
      str_result[i] = ((str_idx + chave_idx) % NUM_LETRAS) + ASCII_A;
    } else {
      perror("Erro: String contem caracteres invalidos.");
      free(str_result);
      exit(EXIT_FAILURE);
    }
  }
  str_result[TAMANHO_SENHA] = '\0'; // Finaliza a string
  return str_result;
}

// Função que escreve a senha encontrada em um arquivo com índice no nome
void EscreveArquivo(const char *senha, int indice) {
  char nome_arquivo[30]; // Buffer para armazenar o nome do arquivo
  snprintf(nome_arquivo, sizeof(nome_arquivo), "dec_passwd_%d.txt", indice);

  FILE *arquivo = fopen(nome_arquivo, "a"); // Abre o arquivo em modo de adição
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo para escrita");
    return;
  }

  fprintf(arquivo, "%s\n", senha); // Escreve a senha no arquivo
  fclose(arquivo);                 // Fecha o arquivo após a escrita
}

// Função que gera combinações de senhas e compara com uma senha criptografada
char *encontraSenhas(char *senha_criptografada_comparar, int indice) {
  char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int len = 26;
  char palavra[5];
  char *possivel_senha;
  char *senha_encontrada = NULL;

  // Loop para gerar todas as combinações possíveis
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      for (int k = 0; k < len; k++) {
        for (int l = 0; l < len; l++) {
          palavra[0] = letras[i];
          palavra[1] = letras[j];
          palavra[2] = letras[k];
          palavra[3] = letras[l];
          palavra[4] = '\0';

          // Criptografa a palavra gerada
          possivel_senha = encrypt(palavra);

          // Compara a senha criptografada gerada com a senha fornecida
          if (strcmp(possivel_senha, senha_criptografada_comparar) == 0) {
            senha_encontrada = malloc(strlen(palavra) + 1);
            if (senha_encontrada == NULL) {
              // Erro na alocação de memória
              return NULL;
            }
            strcpy(senha_encontrada, palavra);
            EscreveArquivo(senha_encontrada, indice);
            return senha_encontrada;
          }
        }
      }
    }
  }
  return NULL; // Retorna NULL se nenhuma correspondência for encontrada
}

// Função para ler o arquivo e processar as senhas
void LerArquivo(const char *nomeArquivo, int indice) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo");
    return;
  }

  char linha[MAX_LINE_LENGTH];

  while (fgets(linha, sizeof(linha), arquivo)) {
    linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
    encontraSenhas(linha, indice);
  }

  fclose(arquivo);
  usleep(500000); // Pausa de 500 milissegundos para melhorar a visualização do
                  // processamento
}

// Função que será utilizada pelas threads
void *thread_func(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;
  printf("Thread #%d: Quebrando senhas de %s\n", args->indice, args->arquivo);
  LerArquivo(args->arquivo, args->indice);
  printf("Thread #%d: Senhas quebradas salvas em dec_passwd_%d.txt\n",
         args->indice, args->indice);
  return NULL;
}

// Função principal
int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Uso: %s -p ou -t <nomes dos arquivos>\n", argv[0]);
    return 1;
  }

  // Armazena o número de arquivos a serem processados
  int num_arquivos = argc - 2;
  clock_t inicio = clock(); // Marca o início do tempo de execução

  if (strcmp(argv[1], "-p") == 0) { // PROCESSOS
    printf("Gerando %d processos para processar arquivos...\n", num_arquivos);
    pid_t processos[num_arquivos];

    for (int i = 0; i < num_arquivos; i++) {
      processos[i] = fork();
      if (processos[i] == 0) { // Código do processo filho
        printf("Processo PID %d: Quebrando senhas de %s\n", getpid(),
               argv[i + 2]);
        LerArquivo(argv[i + 2], i % 10);
        printf(
            "Processo PID %d: Senhas quebradas salvas em dec_passwd_%d.txt\n",
            getpid(), i % 10);
        usleep(500000); // Pausa de 500 milissegundos para melhor visualização
                        // dos processos
        exit(0); // Importante: sair do processo filho após terminar a execução
      }
    }

    // Processo pai aguarda o término de todos os processos filhos
    for (int i = 0; i < num_arquivos; i++) {
      waitpid(processos[i], NULL, 0);
    }

  } else if (strcmp(argv[1], "-t") == 0) { // THREADS
    printf("Criando %d threads para processar arquivos...\n", num_arquivos);
    pthread_t threads[num_arquivos];
    ThreadArgs args[num_arquivos];

    for (int i = 0; i < num_arquivos; i++) {
      args[i].arquivo = argv[i + 2];
      args[i].indice = i % 10; // Índice de 0 a 9
      pthread_create(&threads[i], NULL, thread_func, &args[i]);
      usleep(500000); // Pausa de 500 milissegundos para melhorar a visualização
                      // das threads
    }

    // Aguardando o término de todas as threads
    for (int i = 0; i < num_arquivos; i++) {
      pthread_join(threads[i], NULL);
    }
  } else {
    printf("Opção inválida. Use -p para processos ou -t para threads.\n");
    return 1;
  }

  clock_t fim = clock(); // Marca o fim do tempo de execução
  double tempo_execucao_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) *
                             1000; // Calcula o tempo total em milissegundos
  printf("Tempo de execução: %.2fms\n", tempo_execucao_ms);

  return 0;
}
