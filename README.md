# Embarcados

Repositorio com o intuito de divulgar atividades desenvolvidas durante a matéria de sistemas embarcados da UTFPR - campus Toledo.

# Atividades

## Interfaces de Entrada/Saída

Componentes: 
* Placa módulo TWR-MCF5225X do kit Tower
* Placa elevador primário do kit Tower
* Placa elevador secundário do kit Tower
* Placa módulo TWR-SER do kit Tower
* Cabo de comunicação serial RS-232 DB 9 macho-fêmea
* Programa Terminal ou Hiperterminal
* Conversor USB-Serial (opcional)

### Comunicação serial RS-232

Utilizando o Processor Expert, desenvolva um programa que comunique via serial padrão RS-232 com um computador.

1. Configure a interface serial para: Baud Rate=9600 bps, length:8, parity: none. Além disso, você deve utilizar a interrupção de Rx. Se tiver dúvidas em como configurar o Processor Expert.
2. O programa deve realizar as seguintes funções:
    - Se a chave SW1 for pressionada o programa deverá enviar um comando em código ASCII “L1L;” e o LED1 deve acender.
    - Se a chave SW2 for pressionada o programa deverá enviar um comando em código ASCII “L2L;” e o LED2 deve acender.
    - Se a chave SW1 for pressionada novamente o programa deverá enviar um comando em código ASCII “L1D;” e o LED1 deve apagar.
    - Se a chave SW2 for pressionada novamente o programa deverá enviar um comando em código ASCII “L2D;” eo LED2 deve apagar.
    - Se recebido pela serial o comando “L1L;” deve acender o LED1.
    - Se recebido pela serial o comando “L2L;” deve acender o LED2.
    - Se recebido pela serial o comando “L1D;” deve apagar o LED1.
    - Se recebido pela serial o comando “L2D;” deve apagar o LED2.

Se o computador demorar mais que 100ms(timeout) para enviar o próximo caractere, o programa deve descartar os dados recebidos anteriormente e entender que se trata de um novo começo de mensagem.

3. Acrescente ao seu programa uma máquina de estado para reconhecer a seguinte linguagem:
    * {b (ab)^n b | n ≥ 0} – usar esse para os Kits de 1 a 5
    * { ba^n ba | n ≥ 0} - usar esse para os Kits de 6 a 10
    * {a^m b^n | m+n é par} - usar esse para os Kits de 11 a 15
    * {ab^mba(ab)^n | m, n ≥ 0} - usar esse para os Kits de 16 a 20

Obs.: (ab)^n :se n = 0, (ab)^0 = cadeia vazia, se n = 1, (ab)^1 = ab, se n = 2, (ab)^2 = abab, etc
Quando uma cadeia válida for reconhecida os leds 3 e 4 devem acender por 2 segundos e apagar.

### Conversor Analógico Digital - Potenciômetro

Você deverá desenvolver um programa que meça a tensão do potenciômetro e envie o valor via serial.

1. Utilizando o Processor Expert, configure o AD (Insira o componente: Measurement->Measure..->MeasureAnanlog Input), para que meça o valor do potenciômetro e envie via serial para o computador. Consulte o Manual da placa TWR-MCF5225Xdo kit Tower para saber qual pino do
microcontrolador está conectado ao potenciômetro.

2. Dica:Use a função Measure(channel)==ERROK para iniciar a conversão e verificar o fim da conversão e a função GetValue para ler o valor convertido.

3. Observe os valores que são recebidos no computador para cada valor extremo do potenciômetro e faça com que os 4LEDs da placa seja acendidos sequencialmente a medida que a tensão do potenciômetro vai aumentando.

4. Deve ser mostrado no computador o valor da tensão medida no potenciômetro, variando de 0 V a 3,3 V. Não será aceito valores em binário ou hexadecimal. Deve-se utilizar os 12 bits do conversor analógico digital, não será aceito efetuar somente a leitura dos 8 bits mais significativos ou dos 8 bits menos significativos.

### Conversor Analógico Digital –Acelerômetro

Nesta parte você deverá desenvolver um programa que meça o sinal do acelerômetro e envie o valor via serial.

1. Utilizando o Processor Expert, configure o AD, para que meça o valor do acelerômetro nos eixos x, y e z e envie os valores via serial para ocomputador. Consulte o Manual da placa TWR-MCF5225Xdo kit Tower para saber qual pino do microcontrolador está conectado ao potenciômetro.

2. Para conseguir visualizar o valor dos 3 eixos do acelerômetro coloque um caracter de espaço entre cada valor e mande um caracter de nova linha após enviar o valor do último eixo.

3. Verifique os valores extremos de cada eixo inclinando a placa. Configure os LEDs para que acendam de acordo com a inclinação como na Figura 1.

4. No computador deve ser mostrado os valores da inclinação em graus de -90 graus a 90 graus para cada eixo. Não será aceito valores em binário ou hexadecimal. Deve-se utilizar os 12 bits do conversor analógico digital, não será aceito efetuar somente a leitura dos 8 bits mais significativos ou dos 8 bits menos significativos.

Figura 01:

![leds](https://github.com/capsmilani/embarcados/blob/main/figura.png?raw=true)


