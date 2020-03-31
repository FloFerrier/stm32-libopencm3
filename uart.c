#include "uart.h"

void vUART_Setup(void)
{
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA,
                  GPIO_MODE_AF,
                  GPIO_PUPD_NONE,
                  GPIO2);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA,
                  GPIO_MODE_AF,
                  GPIO_PUPD_NONE,
                  GPIO3);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO3);

  rcc_periph_clock_enable(RCC_USART2);
  nvic_disable_irq(NVIC_USART2_IRQ);
  usart_disable_rx_interrupt(USART2);
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  nvic_set_priority(NVIC_USART2_IRQ, 127);
  usart_enable_rx_interrupt(USART2);
  usart_enable(USART2);
  nvic_enable_irq(NVIC_USART2_IRQ);
}

int8_t xUART_Send(char* p_str)
{
  if(p_str == 0)
  {
    return -1;
  }

  while(*p_str != 0)
  {
    usart_send_blocking(USART2, (uint16_t)*p_str);
    p_str++;
  }
  return 0;
}