/*
===============================================================================
 Name        : GPIO_Punteros.c
 Author      : Gustavo Fresno
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) //1.2 led rojo
{
	unsigned int *p;
	unsigned int i;

    p = (unsigned int *)0x40048080; //SYSAHBCLKCTRL0
    *p |= (1 << 6) | (1 << 20);

    p = (unsigned int *)0x40044098;	//IOCON P1_2
    *p = 0;

    p = (unsigned int *)0xA0002384;	//DIR P1_2
    *p = (1 << 2);

    while(1)
    {
        //
    	p = (unsigned int *)0xA0002204;	//SET P1_2
    	*p = (1 << 2);

    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);

    	p = (unsigned int *)0xA0002284;	//CLR P1_2
    	*p = (1 << 2);

    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    	for(i = 0 ; i < 50000 ; i++);
    }
    return 0 ;
}
