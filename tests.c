/*
 * Ricardo Frederico Leuck Filho
 * TRABALHO FINAL - ESTRUTURAS DE DADOS 2017/1
 */

#include<assert.h>  /* Todas as bibliotecas padrao ANSI C            */
#include<ctype.h>   /* O compilador se encarrega de retirar qualquer */
#include<errno.h>   /* biblioteca nao utilizada.                     */
#include<float.h>
#include<limits.h>
#include<locale.h>
#include<math.h>
#include<setjmp.h>
#include<signal.h>
#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "wowlib.h"

int main ()
{
	NODO_P *nodo;
	PESSOA *p1, *p2, *p3;
	LISTA_P *l;
	ARVORE *logins, *nomes;
	int i, status;
	char c, *s;
	s=malloc(sizeof(char)*5);
	strcpy(s,"abcx");

	l=criaListaP();
	p1=criaPessoa("joao","Joao");
	p2=criaPessoa("joaa","Ana");
	adicionaP(l,p1);
	adicionaP(l,p2);

	adicionaP(l,p2);

	logins = criaArvore('l');
	nomes = criaArvore('n');
	for (c='z';c>'a';c--) {
		s[3]=c;
		p3=criaPessoa(s,"Joao S");
		//printf("%s -> lista\n",s);
		adicionaP(l,p3);
		//printf("%s -> arvore de logins\n",s);
		cadastraP(p3,logins);
		//printf("%s -> arvore de nomes\n",s);
		cadastraP(p3,nomes);
	}
	destroiListaP(l);
	l = pesquisaArvore("Joao S",'n',nomes);
	imprimeListaP(l);
	destroiListaP(l);
	l = pesquisaArvore("abcd",'l',logins);
	imprimeListaP(l);
	criaRelacao( pesquisaLogin("abcd",logins), pesquisaLogin("abcx",logins), 123.0);
	criaRelacao( pesquisaLogin("abcd",logins), pesquisaLogin("abcx",logins), 124.0);
	imprimeListaR( pesquisaLogin("abcd",logins)->emprestimos );

}
