/*
 * Ricardo Frederico Leuck Filho
 * TRABALHO FINAL - ESTRUTURAS DE DADOS 2017/1
 * TRAB.c - interface e definicao dos menus
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
RECENTES *hist;
GRAFO *g;

int main ()
{
	logins = criaArvore('l');
	nomes = criaArvore('n');
    hist = inicializaTR();
	printf("\n  --== WHO OWES WHO ==--\n");
	printf("\tBem vindo!\n\n");
	while ( mainMenu() );
    destroiGrafo(g);
}

int mainMenu() {
	int opt=-1;
    char *aux;
	printf("==============\n");
	printf("Menu Principal\n");
	printf("==============\n");
	printf("  1. Cadastro\n");
	printf("  2. Financeiro\n");
	printf("  3. Salvar dados\n");
	printf("  4. Carregar dados\n\n");
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
                printf("-> Salvar dados\n\nNome do arquivo: ");
                aux = lerstring();
                saveData(aux,nomes);
                free(aux);
                aux=NULL;
			} break;
		case 4: {
                printf("-> Carregar dados\n\nNome do arquivo: ");
                aux = lerstring();
                loadData(aux,logins,nomes);
                free(aux);
                aux=NULL;
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
	int opt=-1, err;
	char *login, *nome;
	PESSOA *p;
    LISTA_P *lp;

	printf("=============\n");
	printf("Menu Cadastro\n");
	printf("=============\n");
	printf("  1. Consulta por Nome\n");
	printf("  2. Consulta por Nome (exato)\n");
	printf("  3. Consulta por Login\n");
	printf("  4. Consulta por Login (exato)\n");
	printf("  5. Adiciona registro\n");
	printf("  6. Remove registro\n");
	printf("  7. Lista todos usuarios\n\n");
	printf("  0. Voltar\n\n");
	sscanf(lerstring(),"%d",&opt);
	printf("\n");
	switch ( opt ) {
		case 1: {
                lp = criaListaP();
				printf("-> Consulta por Nome\n");
				printf("-> Nome: ");
                nome = lerstring();
				imprimeListaP(
						percorreArvore(
							pesquisaNodoArvore(
								nome,
								nomes->filho)->filho,
                            lp
							)
					     );
                free(nome);
                nome=NULL;
                destroiListaP(lp);
                lp=NULL;
			} break;
		case 2: {
				printf("-> Consulta por Nome\n");
				printf("-> Nome: ");
                nome = lerstring();
				imprimeListaP(
							pesquisaArvore(
								nome,
                                'n',
								nomes)
					     );
                free(nome);
                nome=NULL;
			} break;
		case 3: {
                lp = criaListaP();
				printf("-> Consulta por Login\n");
				printf("-> Login: ");
                login = lerstring();
				imprimeListaP(
						percorreArvore(
							pesquisaNodoArvore(
								login,
								logins->filho),
							lp
							)
					     );
                free(login);
                login=NULL;
                destroiListaP(lp);
                lp=NULL;
			} break;
		case 4: {
				printf("-> Consulta por Login (exata)\n");
				printf("-> Login: ");
                login = lerstring();
				imprimeListaP(
						pesquisaArvore(
							login,
							'l',
							logins)
					     );
                free(login);
                login=NULL;
			} break;
		case 5: {
				printf("-> Adiciona registro\n");
				printf("-> Nome: ");
				nome = lerstring();
				printf("-> Login: ");
				login = lerstring();
				p = criaPessoa(login,nome);
				err = cadastraP( p, logins);
				err += cadastraP( p, nomes);
				if (err!=0) printf("Erro: nao foi possivel cadastrar.\n");
                free(nome);
                nome=NULL;
                free(login);
                login=NULL;
			} break;
		case 6: {
			} break;
		case 7: {
                printf("-> Lista todos usuarios\n\n");
                lp = criaListaP();
                imprimeListaP(
                        percorreArvore( nomes->filho, lp )
                        );
                destroiListaP(lp);
                lp=NULL;
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
	int opt=-1;
	float valor;
	char *login1, *login2;
    RELACAO *r;
    NODO_R *nodo_relacao;
    PESSOA *p;
	printf("===============\n");
	printf("Menu Financeiro\n");
	printf("===============\n");
	printf("  1. Consulta dividas de um login (exato)\n");
	printf("  2. Consulta balanco de um login (exato)\n");
	printf("  3. Adiciona registro\n");
	printf("  4. Remove registro\n");
	printf("  5. Historico (ultimas 10 transacoes)\n");
	printf("  6. Grafo de vinculos financeiros\n\n");
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
                printf("-> Consulta balanco de um login (exato)\n");
				printf("-> Login: ");
                login1 = lerstring();
                p = pesquisaLogin( login1, logins);
                if ( p==NULL ) {
                    printf("Login nao encontrado\n");
                    return 1;
                }
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
                r = NULL;
                r = criaRelacao(
                        pesquisaLogin(login1,logins),
                        pesquisaLogin(login2,logins),
                        valor);
				if ( r!=NULL ) {
					printf("Divida Inserida\n");
					printf("%s emprestou a %s $%.2f\n",login1,login2,valor);
                    lembrar(r,hist);
				}
				else {
					printf("Erro: divida nao pode ser inserida.\n");
				}
                free(login1);
                free(login2);
			} break;
		case 4: {
			} break;
		case 5: {
                printf("-> Historico (ultimas 10 transacoes)\n\n");
                imprimeHist(hist);
                printf("\n");
			} break;
		case 6: {
                printf("-> Grafo de vinculos financeiros\n\n");
                g = geraGrafo(nomes);
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
