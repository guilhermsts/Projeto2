\mainpage Documentação Projeto 2, SETR
## Introdução
Segundo projeto desenvolvido na cadeira de SETR, Sistemas Embutidos e de Tempo Real, onde consiste na implementação de um módulo em C que processe comandos recebidos via UART, um caracter de cada vez. O modulo é parte de um sensor inteligentre que permite a leitura de temperarura (-50ºC ... 60ºC), da humidade relativa (0 ... 100%) e de CO2 (400 ... 20000 ppm).

## Especificações 
Estrutura dos comandos:  **# CMD DATA CS !**
* **- #**: um byte, símbolo de inicio do frame
* **- CMD**: um byte, indicação do comando
* **- DATA**: tamanho variável, argumentos do comando
* **- CS**: um byte, checksum. Somatório do valor numérico de CMD e DATA[i] bytes
* **- !**: um byte, símbolo de fim do frame

Todas as comunicações são em ASCII. E. g. se a temperatura for +25ºC, os bytes correspondentes serão 43 ('+'), 50 ('2') e 53 ('5').

Comandos suportados:
* **- A**: lê os valores, em tempo real, fornecidos pelo sensore
* **- P**: lê um dos valores, em tempo real, fornecidos pelo sensor (mostra ou a temperatura ou a humidade ou o CO2)
* **- L**: retorna os últimos 20 valores lidos para cada variável 
* **- R**: restaura o histórico

## Ficheiros 
* **cmdproc (.c/.h)**: Ficheiros header e sua respetiva implementação do módulo de processamento dos comandos recebidos via UART
* **sensors (.c/.h)**: Ficheiros header e sua respetiva implementação do sensor que faz a leitura dos três parâmetros
* **unity (.c/.h)**: Ficheiros header e sua respetiva implementação das funções a utilizar para o teste dos módulos a desenvolver (ficheiros retirados da comunidade ThrowTheSwitch.org github )
* **main.c**: Integração e implementação do módulo e sensores 
* **test.c**: Ficheiro para teste específico das funções desenvolvidas
* **README.md**: Instruções de compilação e para abrir documentação html
* **MAINPAGE.md**: Ficheiro de configuração da página principal html 

\author Guilherme Santos, gui.santos@ua.pt
\author Francisco Bastos, fcbastos4@ua.pt
