Quebra Senhas
Este projeto é um programa em C para quebra de senhas utilizando criptografia simples. O programa pode ser executado utilizando processos ou threads para processar arquivos de entrada e encontrar senhas criptografadas.

Requisitos
GCC (ou outro compilador C compatível)
Sistema operacional Unix-like (Linux, macOS) para execução de processos e threads
Estrutura do Projeto
quebra_senhas.c - Código fonte principal do programa
README.md - Documentação do projeto
Compilação
Para compilar o código, use o comando gcc com as seguintes opções:

bash
Copiar código
gcc -o quebra_senhas quebra_senhas.c -pthread
Aqui está o que cada opção faz:

-o quebra_senhas - Especifica o nome do executável gerado.
-pthread - Adiciona suporte a threads POSIX.
Execução
Utilizando Processos
Para executar o programa usando processos, utilize a opção -p:

bash
Copiar código
./quebra_senhas -p <arquivo1> <arquivo2> ... <arquivoN>
Onde <arquivo1>, <arquivo2>, etc., são os arquivos contendo as senhas criptografadas a serem processadas.

Exemplo:

bash
Copiar código
./quebra_senhas -p passwd_0.txt passwd_1.txt
Isso criará um processo para cada arquivo especificado.

Utilizando Threads
Para executar o programa usando threads, utilize a opção -t:

bash
Copiar código
./quebra_senhas -t <arquivo1> <arquivo2> ... <arquivoN>
Onde <arquivo1>, <arquivo2>, etc., são os arquivos contendo as senhas criptografadas a serem processadas.

Exemplo:

bash
Copiar código
./quebra_senhas -t passwd_0.txt passwd_1.txt
Isso criará uma thread para cada arquivo especificado.

Funcionamento
Criação de Processos/Threads:

O programa cria um processo ou thread para cada arquivo fornecido.
Cada processo ou thread lerá o arquivo e tentará quebrar as senhas criptografadas.
Quebra de Senhas:

O programa gera combinações possíveis de senhas de 4 letras (AAAA a ZZZZ).
Cada combinação é criptografada e comparada com as senhas criptografadas fornecidas.
Escrita dos Resultados:

Se uma senha correspondente for encontrada, ela é salva em um arquivo com o nome dec_passwd_X.txt, onde X é o índice do arquivo (0 a 9).
Tempo de Execução:

O tempo total de execução do programa é exibido em milissegundos.
Exemplo de Saída
Execução Usando Processos
yaml
Copiar código
Gerando 3 processos para processar arquivos...
Processo PID 1234: Quebrando senhas de passwd_0.txt
Processo PID 1235: Quebrando senhas de passwd_1.txt
Processo PID 1236: Quebrando senhas de passwd_2.txt
Processo PID 1234: Senhas quebradas salvas em dec_passwd_0.txt
Processo PID 1235: Senhas quebradas salvas em dec_passwd_1.txt
Processo PID 1236: Senhas quebradas salvas em dec_passwd_2.txt
Tempo de execução: 700ms
Execução Usando Threads
bash
Copiar código
Criando 3 threads para processar arquivos...
Thread #0: Quebrando senhas de passwd_0.txt
Thread #1: Quebrando senhas de passwd_1.txt
Thread #2: Quebrando senhas de passwd_2.txt
Thread #0: Senhas quebradas salvas em dec_passwd_0.txt
Thread #1: Senhas quebradas salvas em dec_passwd_1.txt
Thread #2: Senhas quebradas salvas em dec_passwd_2.txt
Tempo de execução: 500ms
Contribuição
Sinta-se à vontade para enviar pull requests, relatar problemas ou sugerir melhorias. Para contribuir, siga as melhores práticas de codificação e teste suas alterações antes de enviar.

Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo LICENSE para mais detalhes.
