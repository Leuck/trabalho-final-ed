/*
 * Ricardo Frederico Leuck Filho
 * TRABALHO FINAL - ESTRUTURAS DE DADOS 2017/1
 * FUNCOES
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

// FUNCOES
PESSOA * criaPessoa(char *login, char *nome) {
	PESSOA *p;
	int i;
	char c;
	for (i=0;i<strlen(login);i++){
		c=login[i];
		if ( !( (c>='0' && c<='9') || (c>='a' && c<='z') || (c=='_') ) ) {
			fprintf(stderr,"Erro: Login invalido.\n");
			return NULL;
		}
	}
	for (i=0;i<strlen(nome);i++){
		c=nome[i];
		if ( !( (c>='A' && c<='Z') || (c>='a' && c<='z') || (c==' ') ) ) {
			fprintf(stderr,"Erro: Nome invalido.\n");
			return NULL;
		}
	}
	
	p = malloc(sizeof(PESSOA));
	p->login = malloc(sizeof(char)*(strlen(login)+1));
	strcpy(p->login,login);
	p->nome = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(p->nome,nome);
	p->dividas = malloc(sizeof(LISTA_R));
	p->dividas->ini = NULL;
	p->dividas->tam = 0;
	p->emprestimos = malloc(sizeof(LISTA_R));
	p->emprestimos->ini = NULL;
	p->emprestimos->tam = 0;
	p->amigos = malloc(sizeof(LISTA_P));
	p->amigos->ini = NULL;
	p->amigos->tam = 0;
	return p;
}
// --LISTA ENCADEADA DE PESSOAS
LISTA_P * criaListaP() {
	// cria e inicializa uma lista de pessoas
	LISTA_P *l;
	l = malloc(sizeof(LISTA_P));
	l->ini = NULL;
	l->tam = 0;
	return l;
}
void destroiListaP(LISTA_P *l) {
	NODO_P *aux1, *aux2;
	if (l->ini==NULL) {
		free(l);
		return;
	}
	aux1 = l->ini;
	while ( aux1!=NULL ) {
		aux2=aux1->prox;
		free(aux1);
		aux1=aux2;
	}
	free(l);
}
void imprimeListaP(LISTA_P *l) {
	//mostra lista de pessoas no tela
	NODO_P *aux;
	if (l==NULL) {
		printf("Lista vazia.\n");
		return;
	}
	aux = l->ini;
	while (aux!=NULL) {
		printf("%s (%s)\n",aux->p->nome,aux->p->login);
		aux=aux->prox;
	}
}
void adicionaP(LISTA_P *l, PESSOA *p) {
	// adiciona uma pessoa a lista
	int cmp1, cmp2;
	NODO_P *n, *aux1, *aux2;
	char *novo, *saux1, *saux2;
	if (p == NULL || l == NULL) return;
	if (p->login == NULL) return; // verifica pessoa
	if (p->nome == NULL) return; // verifica pessoa
	n = malloc(sizeof(NODO_P));
	n->p = p;
	// se a lista esta vazia
	if (l->ini==NULL) {
		l->ini = n;
		l->tam = 1;
		n->prox = NULL;
	}
	else { // percorremos a lista e inserimos em ordem alfabetica de login
		aux1=l->ini;
		novo = p->login;
		saux1 = aux1->p->login;
		cmp1 = strcmp(novo,saux1);
		if (cmp1<0) {
			l->ini=n;
			n->prox=aux1;
			l->tam++;
		}
		else {
			while ( 1 ) {
				// strcmp (novo, saux)
				//   retorna > 0 quando novo maior que saux
				//   retorna < 0 quando novo menor que saux
				//   retorna = 0 quando novo igual a saux
				cmp1 = strcmp(novo,saux1);
				if (aux1->prox!=NULL) {
					aux2 = aux1->prox;
					saux2 = aux2->p->login;
					cmp2 = strcmp(novo,saux2);
					if (cmp1 == 0 || cmp2 == 0) {
						fprintf(stderr,"Erro: login existente.\n");
						return;
					}
					else if (cmp1>0 && cmp2<0) {
						aux1->prox=n;
						l->tam++;
						n->prox=aux2;
						return;
					}
					else if (cmp1>0 && cmp2>0) {
						aux1=aux1->prox;
					}
				}
				else {
					if (cmp1==0) {
						fprintf(stderr,"Erro: login existente (l).\n");
						return;
					}
					else {
						aux1->prox=n;
						l->tam++;
						n->prox=NULL;
						return;
					}
				}
			}
		}
	}
}
void removeP (LISTA_P *l, char *login) {
	NODO_P *aux1, *aux2;
	if (l==NULL || l->ini==NULL) return;
	aux1 = l->ini;
	aux2 = aux1->prox;
	if ( strcmp(login,aux1->p->login)==0 ) {
		if (aux2==NULL) {
			destroiListaP(aux1->p->amigos);
			destroiListaR(aux1->p->dividas);
			destroiListaR(aux1->p->emprestimos);
			free(aux1);
			l->ini=NULL;
		}
		else {
			l->ini = aux2;
			free(aux1);
		}
	}
	while (aux1!=NULL) {
		aux2 = aux1->prox;
		if ( (strcmp(login,aux1->p->login))==0 ) {
			if (aux2==NULL) {
			}
		}
	}
}
// --LISTA ENCADEADA DE DIVIDAS
LISTA_R * criaListaR() {
	// cria e inicializa uma lista de dividas
	LISTA_R *l;
	l = malloc(sizeof(LISTA_R));
	l->ini = NULL;
	return l;
}
void destroiListaR(LISTA_R *l) {
	NODO_R *aux1, *aux2;
	if (l->ini==NULL) {
		free(l);
		return;
	}
	aux1 = l->ini;
	while ( aux1!=NULL ) {
		aux2=aux1->prox;
		free(aux1);
		aux1=aux2;
	}
	free(l);
}
void adicionaR(LISTA_R *l, RELACAO *r) {
	// adiciona uma relacao de divida a uma lista de relacoes
	NODO_R *nodo, *aux;
	if (r==NULL || l==NULL) return;
	nodo = malloc(sizeof(NODO_R));
	nodo->r = r;
	if (l->ini == NULL) {
		l->ini = nodo;
		nodo->prox = NULL;
		return;
	}
	else {
		aux=l->ini;
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = nodo;
		nodo->prox = NULL;
	}
}
RELACAO * criaRelacao(PESSOA *credor, PESSOA *devedor, float valor) {
	RELACAO *r;
	if (credor==NULL || devedor==NULL || valor<=0) {
		fprintf(stderr,"Erro: relacao invalida.\n");
		return NULL;
	}
	r = malloc(sizeof(RELACAO));
	r->credor = credor;
	r->devedor = devedor;
	r->valor = valor;
	adicionaR(credor->emprestimos, r);
	adicionaR(devedor->dividas, r);
	return r;
}
void imprimeListaR(LISTA_R *l) {
	//mostra lista de dividas na tela
	NODO_R *aux;
    if ( l->ini==NULL ) printf("Lista vazia.\n");
	aux = l->ini;
	while (aux!=NULL) {
		printf("%s (%s) deve $%.2f a %s (%s)\n",
				aux->r->devedor->nome,
				aux->r->devedor->login,
				aux->r->valor,
				aux->r->credor->nome,
				aux->r->credor->login);
		aux=aux->prox;
	}
}
// ARVORE DE PESQUISA
ARVORE * criaArvore(char t) {
	ARVORE *a;
	if (t!='l' && t!='n') return NULL;
	a = malloc(sizeof(ARVORE));
	a->filho = NULL;
	a->t = t;
	return a;
}
NODO_A *criaNodoA(char chave) {
	NODO_A *n;
	n = malloc(sizeof(NODO_A));
	if (n==NULL) {
		fprintf(stderr,"Erro: memoria cheia!\n");
		return NULL;
	}
	n->chave = chave;
	n->filho = NULL;
	n->irmao = NULL;
	n->l = criaListaP();
	return n;
}
LISTA_P * percorreArvore( NODO_A *raiz, LISTA_P *l) {
	// percorre arvore adicionando as pessoas encontradas a uma lista
	NODO_P *aux;
	if (raiz==NULL || l==NULL) return NULL;
	aux = raiz->l->ini;
	while (aux!=NULL) {
		adicionaP(l,aux->p);
		aux = aux->prox;
	}
	if (raiz->filho!=NULL) percorreArvore( raiz->filho, l );
	if (raiz->irmao!=NULL) percorreArvore( raiz->irmao, l );
	return l;
}
NODO_A * inserePessoaNaArvore( char *nome, NODO_A *raiz) {
	//
	// retornar nodo onde pessoa deve ser inserida
	//  se primeiro caractere do nome == chave da raiz
	//    se fim do nome:
	//      inserir aqui
	//    se nao fim do nome:
	//      se raiz não tem filho: 
	//        cria filho
	//        inserePessoa (proximo c, filho da raiz)
	//      se raiz tem filho:
	//        se chave do filho > proximo c:
	//          aux = filho
	//          filho = criaNodo(proximo c)
	//          irmao do filho = aux
	//        inserePessoa( proximo c, filho da raiz )
	//  se primeiro char do nome != chave da raiz
	//    se raiz nao tem irmao:
	//      cria irmao
	//      inserePessoa (mesmo c, irmao da raiz)
	//    se raiz tem irmao:
	//      se chave da raiz < primeiro char do nome < chave do irmao:
	//        aux = irmao
	//        irmao = criaNodo(chave = primeiro char do nome)
	//        irmao->irmao = aux
	//      inserePessoa (mesmo c, irmao da raiz)
	//
	NODO_A *aux;
	if (nome[0] == raiz->chave) {
		if ( nome[1]=='\0' ) {
			return raiz;
		}
		else {
			if ( raiz->filho==NULL ) {
				raiz->filho = criaNodoA(nome[1]);
				return inserePessoaNaArvore( &nome[1], raiz->filho );
			}
			else {
				if (raiz->filho->chave > nome[1]) {
					aux = raiz->filho;
					raiz->filho = criaNodoA(nome[1]);
					raiz->filho->irmao = aux;
				}
				return inserePessoaNaArvore( &nome[1], raiz->filho );
			}
		}
	}
	else {
		if ( raiz->irmao==NULL ) {
			raiz->irmao = criaNodoA(nome[0]);
			return inserePessoaNaArvore( &nome[0], raiz->irmao );
		}
		else {
			if ( nome[0] > raiz->chave && nome[0] < raiz->irmao->chave ) {
				aux = raiz->irmao;
				raiz->irmao = criaNodoA(nome[0]);
				raiz->irmao->irmao = aux;
			}
			return inserePessoaNaArvore( &nome[0], raiz->irmao );
		}
	}
}	
int cadastraP(PESSOA *p, ARVORE *a) {
	// Adiciona pessoa a arvore de pesquisa
	// sucesso: retorna 0
	// erro: retorna !=0
	char *nome=NULL;
	NODO_A *aux;
	if (p==NULL) return 1;
	if (a==NULL) return 2;
	if (a->t=='l') nome=p->login;		// arvore de pesquisa de logins
	else if (a->t=='n') nome=p->nome;	// arvore de pesquisa de nomes
	else return 3;
	if (a->filho==NULL) { // arvore vazia
		a->filho = criaNodoA(nome[0]);
		if (a->filho == NULL) return 4;
	}
	else if (nome[0] < a->filho->chave) {
		aux = a->filho;
		a->filho = criaNodoA(nome[0]);
		a->filho->irmao = aux;
		aux=NULL;
	}
	aux = inserePessoaNaArvore( nome, a->filho);
	adicionaP(aux->l,p);
	return 0;
}
NODO_A * pesquisaNaArvore (char *nome, NODO_A *raiz) {
	//
	// Retorna nodo correspondente a nome
	// se primeiro char de nome == chave da raiz
	//   se fim do nome:
	//     retorna raiz
	//   se nao fim do nome E raiz possui filhos:
	//     pesquisaNaArvore( proximo char, filho da raiz )
	//   else
	//     retorna NULL
	// se primeiro char de nome != chave da raiz:
	//   se raiz possui irmao:
	//     pesquisaNaArvore( mesmo char, irmao da raiz)
	//   se raiz nao possui irmao:
	//     retorna NULL
	//
	if ( nome[0]==raiz->chave ){
		if ( nome[1] == '\0' ) return raiz;
		else if ( raiz->filho!=NULL ) return pesquisaNaArvore( &nome[1],raiz->filho);
		else return NULL;
	}
	else {
		if ( raiz->irmao != NULL ) return pesquisaNaArvore( nome,raiz->irmao );
		else return NULL;
	}
}
LISTA_P * pesquisaArvore(char *nome, char tipo, ARVORE *a) {
	// retorna a lista de logins relativos a um nome na arvore de pesquisa de nomes
	NODO_A *aux;
	if (tipo!='l' && tipo!='n') {
		fprintf(stderr,"Erro: pesquisaArvore(): tipo invalido.\n");
		return NULL;
	}
	if (a->t!=tipo) {
		fprintf(stderr,"Erro: pesquisaArvore(): tipo de arvore incorreto.\n");
		return NULL;
	}
	if (a->filho==NULL) {
		fprintf(stderr,"Erro: pesquisaArvore(): arvore vazia.\n");
		return NULL;
	}
	aux = pesquisaNaArvore(nome, a->filho);
	if (aux==NULL) return NULL;
	return aux->l;
}
PESSOA * pesquisaLogin(char *login, ARVORE *a) {
	LISTA_P *lista;
	lista = pesquisaArvore(login,'l',a);
	if (lista==NULL) return NULL;
	else if (lista->ini==NULL) return NULL;
	else return lista->ini->p;
}

// CADASTRO DE DIVIDAS

// LerString
char *lerstring () {
	char buffer[500], *str;
	do {
		fgets(buffer,499,stdin);
	} while( strcmp(buffer, "\n")==0 );
	*(strchr(buffer,'\n'))='\0';
	str = (char*) malloc((strlen(buffer)+1)*sizeof(char));
	strcpy(str,buffer);
	return str;
}
