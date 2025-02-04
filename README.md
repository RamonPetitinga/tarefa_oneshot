Para utiliza-lo, basta clonar o repositorio, compilar o arquivo "oneshot.c" e executa-lo a partir do "diagram.json" - simulador Wokwi.

Visualize também pelo site:

https://wokwi.com/projects/421921030101441537

⏳ Temporizador Periódico com Raspberry Pi Pico

Este projeto implementa um temporizador periódico utilizando o Raspberry Pi Pico. O sistema aciona um conjunto de LEDs em um ciclo predefinido ao pressionar um botão.

🔧 Funcionalidades

    Pressionar o botão inicia uma sequência de iluminação dos LEDs.
    Os LEDs mudam de estado a cada 3 segundos.
    O ciclo finaliza após três estados e aguarda uma nova ativação pelo botão.

📌 Configuração dos Pinos
Componente GPIO
LED Vermelho 11
LED Verde 12
LED Azul 13
Botão 5

⚙ Como Funciona

O sistema inicia com todos os LEDs apagados.

Quando o botão é pressionado, o temporizador é ativado e os LEDs seguem a seguinte sequência:

1️⃣ Estado 0 – Todos os LEDs acendem.
2️⃣ Estado 1 – LED azul apaga.
3️⃣ Estado 2 – O LED vermelho apaga, permanecendo apenas o verde.
4️⃣ Estado 3 – Todos os LEDs se apagam e o ciclo é concluído.

O sistema aguarda uma nova ativação pelo botão para repetir o ciclo.
