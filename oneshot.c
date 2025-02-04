#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e botão.
#define BUTTON_PIN 5
#define led_vermelho 11
#define led_verde 12
#define led_azul 13

// Definição do stado do sistema.
volatile bool aguardando_reset = false;

// Função para desligar o LED azul (último).
int64_t apagar_led_azul(alarm_id_t id, void *user_data)
{
    gpio_put(led_azul, 0);
    aguardando_reset = false; // Permite nova ativação pelo botão.
    printf("Aguardando botão ser pressionado...\n");
    return 0;
}

// Função para desligar o LED verde.
int64_t apagar_led_verde(alarm_id_t id, void *user_data)
{
    gpio_put(led_verde, 0);
    // Programa o desligamento do LED azul após mais 3s.
    add_alarm_in_ms(3000, &apagar_led_azul, NULL, false);
    return 0;
}

// Função para desligar o LED vermelho.
int64_t apagar_led_vermelho(alarm_id_t id, void *user_data)
{
    gpio_put(led_vermelho, 0);
    // Programa o desligamento do LED verde após mais 3s.
    add_alarm_in_ms(3000, &apagar_led_verde, NULL, false);
    return 0;
}

//  Função de interrupção do botão.
void gpio_irq_handler(uint gpio, uint32_t events)
{
    if (!aguardando_reset)
    {
        gpio_put(led_vermelho, 1);
        gpio_put(led_verde, 1);
        gpio_put(led_azul, 1);
        aguardando_reset = true;

        // Inicia os timers para apagar os LEDs na sequência correta.
        add_alarm_in_ms(3000, &apagar_led_vermelho, NULL, false); //
    }
}

int main()
{
    stdio_init_all();
    int tempo = 1;

    // Inicialização do led vermelho
    gpio_init(led_vermelho);
    gpio_set_dir(led_vermelho, GPIO_OUT);
    gpio_put(led_vermelho, 0);

    // Inicialização do led verde.
    gpio_init(led_verde);
    gpio_set_dir(led_verde, GPIO_OUT);
    gpio_put(led_verde, 0);

    // Inicialização do led azul.
    gpio_init(led_azul);
    gpio_set_dir(led_azul, GPIO_OUT);
    gpio_put(led_azul, 0);

    // Inicialização do botão.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Interrupção provocada pelo botão.
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Loop principal para rodar infinitamente.
    while (true)
    {
        printf("Se passou %d segundo(s)\n", tempo);
        sleep_ms(1000);
        tempo++;
    }
}