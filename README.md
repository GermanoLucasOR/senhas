Quebra Senhas

Este projeto é um programa em C para quebra de senhas utilizando criptografia simples. O programa pode ser executado utilizando processos ou threads para processar arquivos de entrada e encontrar senhas criptografadas.

Requisitos:
- GCC (ou outro compilador C compatível)
- Sistema operacional Unix-like (Linux, macOS) para execução de processos e threads

Estrutura do Projeto:
- quebra_senhas.c - Código fonte principal do programa
- README.txt - Documentação do projeto

Compilação:
Para compilar o código, use o comando `gcc` com as seguintes opções:

    gcc quebra_senhas.c -o quebra_senhas

Execução:
Utilizando Processos:
Para executar o programa usando processos, utilize a opção -p:

    ./quebra_senhas -p <arquivo1> <arquivo2> ... <arquivoN>
    
Utilizando Threads:
Para executar o programa usando threads, utilize a opção -t:

    ./quebra_senhas -t <arquivo1> <arquivo2> ... <arquivoN>

Funcionamento:
1. Criação de Processos/Threads:
   - O programa cria um processo ou thread para cada arquivo fornecido.
   - Cada processo ou thread lerá o arquivo e tentará quebrar as senhas criptografadas.

2. Quebra de Senhas:
   - O programa gera combinações possíveis de senhas de 4 letras (AAAA a ZZZZ).
   - Cada combinação é criptografada e comparada com as senhas criptografadas fornecidas.

3. Escrita dos Resultados:
   - Se uma senha correspondente for encontrada, ela é salva em um arquivo com o nome dec_passwd_X.txt, onde X é o índice do arquivo (0 a 9).

4. Tempo de Execução:
   - O tempo total de execução do programa é exibido em milissegundos.
