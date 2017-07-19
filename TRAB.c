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

int mainMenu();
int menuCadastro();
int menuDividas();

ARVORE *logins, *nomes;

int main ()
{
	logins = criaArvore('l');
	nomes = criaArvore('n');
	printf("\n  --== WHO OWES WHO ==--\n");
	printf("\tBem vindo!\n\n");
	while ( mainMenu() );
}

int mainMenu() {
	int opt;
	printf("==============\n");
	printf("Menu Principal\n");
	printf("==============\n");
	printf("  1. Cadastro\n");
	printf("  2. Dividas\n");
	printf("  3. Salvar dados\n\n");
	printf("  0. Sair\n\n");
	sscanf(lerstring(),"%d",&opt);
	printf("\n");
	switch ( opt ) {
		case 1: {
				while ( menuCadastro() );
			} break;
		case 2: {
				while ( menuDividas() );
			} break;
		case 3: {
			} break;
		case 0: {
				printf("Bye!\n");
				return 0;
			} break;
		default: {
				 printf("Opcao invalida.\n");
			} break;
	}
	return 1;
}
int menuCadastro() {
	int opt, err;
	char *login, *nome;
	PESSOA *p;

	printf("=============\n");
	printf("Menu Cadastro\n");
	printf("=============\n");
	printf("  1. Consulta por Nome\n");
	printf("  2. Consulta por Login\n");
	printf("  3. Consulta por Login (exata)\n");
	printf("  4. Adiciona registro\n");
	printf("  5. Remove registro\n\n");
	printf("  0. Voltar\n\n");
	sscanf(lerstring(),"%d",&opt);
	printf("\n");
	switch ( opt ) {
		case 1: {
				printf("-> Consulta por Nome\n");
				printf("-> Nome: ");
				imprimeListaP(
						percorreArvore(
							pesquisaNaArvore(
								lerstring(),
								nomes->filho),
							criaListaP()
							)
					     );
			} break;
		case 2: {
				printf("-> Consulta por Login\n");
				printf("-> Login: ");
				imprimeListaP(
						percorreArvore(
							pesquisaNaArvore(
								lerstring(),
								logins->filho),
							criaListaP()
							)
					     );
			} break;
		case 3: {
				printf("-> Consulta por Login (exata)\n");
				printf("-> Login: ");
				imprimeListaP(
						pesquisaArvore(
							lerstring(),
							'l',
							logins)
					     );
			} break;
		case 4: {
				printf("-> Adiciona registro\n");
				printf("-> Nome: ");
				nome = lerstring();
				printf("-> Login: ");
				login = lerstring();
				p = criaPessoa(login,nome);
				err = cadastraP( p, logins);
				err += cadastraP( p, nomes);
				if (err!=0) printf("Erro: nao foi possivel cadastrar.\n");
			} break;
		case 5: {
			} break;
		case 0: {
				return 0;
			} break;
		default: {
				 printf("Opcao invalida.\n");
			} break;
	}
	return 1;
}
int menuDividas() {
	int opt;
	float valor;
	char *login1, *login2;
    NODO_R *nodo_relacao;
    PESSOA *p;
	printf("============\n");
	printf("Menu Dividas\n\n");
	printf("============\n");
	printf("  1. Consulta dividas de um login (exato)\n");
	printf("  2. Consulta balanço de um login (exato)\n");
	printf("  3. Adiciona registro\n");
	printf("  4. Remove registro\n\n");
	printf("  0. Voltar\n\n");
	sscanf(lerstring(),"%d",&opt);
	printf("\n");
	switch ( opt ) {
		case 1: {
                printf("-> Consulta dividas de um login (exato)\n");
				printf("-> Login: ");
                login1 = lerstring();
                printf("Dividas de %s:\n",login1);
                imprimeListaR(
                        pesquisaLogin(
                            login1,
                            logins)->dividas );
			} break;
		case 2: {
                printf("-> Consulta balanço de um login (exato)\n");
				printf("-> Login: ");
                login1 = lerstring();
                p = pesquisaLogin( login1, logins);
                printf("Dividas de %s:\n",login1);
                imprimeListaR( p->dividas );
                printf("Emprestimos de %s:\n",login1);
                imprimeListaR( p->emprestimos );
                valor = 0;
                nodo_relacao = p->emprestimos->ini;
                while (nodo_relacao!=NULL) {
                    valor += nodo_relacao->r->valor;
                    nodo_relacao = nodo_relacao->prox;
                }
                nodo_relacao = p->dividas->ini;
                while (nodo_relacao!=NULL) {
                    valor -= nodo_relacao->r->valor;
                    nodo_relacao = nodo_relacao->prox;
                }
                printf("Balanço: $%.2f\n",valor);
                free(login1);
			} break;
		case 3: {
				printf("-> Login do credor: ");
				login1 = lerstring();
				printf("-> Login do devedor: ");
				login2 = lerstring();
				printf("-> Valor: ");
				scanf("%f",&valor);
				if (criaRelacao(pesquisaLogin(login1,logins),
						pesquisaLogin(login2,logins),
								valor)!=NULL) {
					printf("Divida Inserida\n");
					printf("%s emprestou a %s $%.2f\n",login1,login2,valor);
				}
				else {
					printf("Erro: divida nao pode ser inserida.\n");
				}
                free(login1);
                free(login2);
			} break;
		case 4: {
			} break;
		case 0: {
				return 0;
			} break;
		default: {
				 printf("Opcao invalida.\n");
			} break;
	}
	return 1;
}
