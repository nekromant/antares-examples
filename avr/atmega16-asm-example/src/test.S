#include <avr/io.h>
;; #include <compat/deprecated.h>
#define SFR(X) _SFR_IO_ADDR(X)
#define reg_led r20             
#define temp r16                
#define START 0
#define STOP 1
;; .includepath "/usr/share/avra/includes/" ;Папка с файлами заголовками
;; .include "m16def.inc" ; Используем ATMega16
;; Переключение светодиодов при нажатии на кнопку START
        ;; .def temp =r16
        ;; .def reg_led = r20
        ;; .equ START = 0
        ;; .equ STOP = 1
        ;; .org $000      ;устанавливает начальный адрес первого сегмента
        .section .text
        .global  main

        ;; rjmp init
        ;; Инициализация
main:   ldi reg_led, 0xfe       ;сброс reg_led.0 для включения LED.0
        sec                     ;C=1
        set                     ;T=1 - флаг направления
        ser temp                ;temp = 0xFF
        out SFR(DDRB),temp      ;порта PB на вывод
        out SFR(PORTB), temp    ;погасить LED
        clr temp                ;temp = 0x00
        out SFR(DDRD),temp      ;??переключаем порт D на вход
        ldi temp,0x03           ;включение подтягивающих резисторов
        out SFR(PORTD), temp    ;порта D
waitstart:
        sbic SFR(PIND),START            ;прыжок на +2 если PIND.START==0
        rjmp waitstart

loop:
        out SFR(PORTB),reg_led

