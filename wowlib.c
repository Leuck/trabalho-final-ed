/*
 * Ricardo Frederico Leuck Filho
 * TRABALHO FINAL - ESTRUTURAS DE DADOS 2017/1
 * wowlib.c - FUNCOES
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
    // destroi uma lista de dividas
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
        l->tam = 1;
		nodo->prox = NULL;
		return;
	}
	else {
		aux=l->ini;
        // nao adiciona mesma relacao duas vezes
        if ( r == aux->r ) return;
		while (aux->prox != NULL) {
            if ( r == aux->prox->r ) return;
			aux = aux->prox;
		}
		aux->prox = nodo;
        l->tam++;
		nodo->prox = NULL;
	}
}
void removeR( RELACAO *r) {
}
RELACAO * criaRelacao(PESSOA *credor, PESSOA *devedor, float valor) {
    // cadastra uma divida
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
    // inicializa arvore de pesquisa
	ARVORE *a;
	if (t!='l' && t!='n') return NULL;
	a = malloc(sizeof(ARVORE));
	a->filho = NULL;
	a->t = t;
	return a;
}
NODO_A *criaNodoA(char chave) {
    // cria nodo para arvore de pesquisa
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
    // percorre a partir de um nodo, todos seus filhos e seus irmaos a direita
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
	// retornar nodo onde pessoa deve ser inserida
    //
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
NODO_A * pesquisaNodoArvore (char *nome, NODO_A *raiz) {
	// Retorna nodo correspondente a nome
    //
	// se primeiro char de nome == chave da raiz
	//   se fim do nome:
	//     retorna raiz
	//   se nao fim do nome E raiz possui filhos:
	//     pesquisaNodoArvore( proximo char, filho da raiz )
	//   else
	//     retorna NULL
	// se primeiro char de nome != chave da raiz:
	//   se raiz possui irmao:
	//     pesquisaNodoArvore( mesmo char, irmao da raiz)
	//   se raiz nao possui irmao:
	//     retorna NULL
	//
    if ( raiz==NULL ) {
        printf("Erro: cadastro vazio\n");
        return NULL;
    }
	if ( nome[0]==raiz->chave ){
		if ( nome[1] == '\0' ) return raiz;
		else if ( raiz->filho!=NULL ) return pesquisaNodoArvore( &nome[1],raiz->filho);
		else return NULL;
	}
	else {
		if ( raiz->irmao != NULL ) return pesquisaNodoArvore( nome,raiz->irmao );
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
	aux = pesquisaNodoArvore(nome, a->filho);
	if (aux==NULL) return NULL;
	return aux->l;
}
PESSOA * pesquisaLogin(char *login, ARVORE *a) {
    // procura e retorna pessoa correspondente a login
    // em uma arvore de pesquisa de logins
	LISTA_P *lista;
	lista = pesquisaArvore(login,'l',a);
	if (lista==NULL) return NULL;
	else if (lista->ini==NULL) return NULL;
	else return lista->ini->p;
}

// LerString
char *lerstring () {
	char buffer[500], *str;
	do {
		fgets(buffer,499,stdin);
	} while( strcmp(buffer, "\n")==0 );
    buffer[499]='\n';
	*(strchr(buffer,'\n'))='\0';
	str = (char*) malloc((strlen(buffer)+1)*sizeof(char));
	strcpy(str,buffer);
	return str;
}

// TRANSACOES RECENTES
RECENTES * inicializaTR() {
    //inicializa uma lista de transacoes recentes
    int i;
    RECENTES *l;
    l = malloc(sizeof(RECENTES));
    for (i=0;i<10;i++) l->dados[i]=NULL;
    l->ini=-1;
    l->fin=-1;
    l->tam=0;
    return l;
}
void lembrar(RELACAO *r, RECENTES *l) {
    // adiciona uma relacao a lista de recentes
    // lista circular em contiguidade fisica
    if (r==NULL || l==NULL) return;
    if (l->ini==-1) {
        l->ini = 0;
        l->fin = 0;
        l->tam = 1;
        l->dados[0]=r;
    }
    else if ( (l->ini<=l->fin) && (l->fin<9) ) {
        l->dados[l->fin+1]=r;
        l->fin++;
        l->tam=1+(l->fin-l->ini);
    }
    else if ( (l->fin==9) && (l->ini>=0) ) {
        l->dados[0]=r;
        l->ini++;
        l->fin=0;
        l->tam=1+(l->fin-l->ini);
    }
    else if ( (l->ini>l->fin) && (l->ini<9) ) {
        l->ini++;
        l->fin++;
        l->dados[l->fin]=r;
        l->tam=11-(l->ini-l->fin);
    }
    else if ( (l->ini==9) && (l->fin<9) ) {
        l->ini=0;
        l->fin++;
        l->dados[l->fin]=r;
        l->tam=1+(l->fin-l->ini);
    }
}
RELACAO * acessaHist( RECENTES *l, int pos ) {
    // acessa item da lista de recentes
    int ini, tam;
    ini=l->ini;
    tam=l->tam;
    if ( pos > tam ) return NULL;
    if ( pos+ini>9 ) return l->dados[pos+ini-10];
    if ( pos+ini<=9 ) return l->dados[pos+ini];
    return NULL;
}
void imprimeHist(RECENTES *l) {
    // imprime o conteudo da lista de recentes na tela
    int i;
    RELACAO *r;
    for (i=0; i<l->tam; i++) {
        r=acessaHist(l,i);
		printf("%s (%s) deve $%.2f a %s (%s)\n",
				r->devedor->nome,
				r->devedor->login,
				r->valor,
				r->credor->nome,
				r->credor->login);
    }
}
// GRAFO DE VINCULOS FINANCEIROS
GRAFO * geraGrafo (ARVORE *a) {
    int i, j, n, icredor, idevedor;
    NODO_P *np;
    NODO_R *nr;
    GRAFO *g;
    LISTA_P *lp;
    LISTA_R *lr;
    // obtem lista com todas pessoas
    lp= criaListaP();
    percorreArvore( a->filho, lp );
    // obtem lista com todas relacoes
    lr= criaListaR();
    np = lp->ini;
    while ( np!=NULL ) {
        nr=np->p->dividas->ini;
        while ( nr!=NULL ) {
            adicionaR(lr, nr->r);
            nr = nr->prox;
        }
        nr=np->p->emprestimos->ini;
        while ( nr!=NULL ) {
            adicionaR(lr, nr->r);
            nr = nr->prox;
        }
        np=np->prox;
    }
    // aloca matriz de relacoes
    n = lp->tam;
    g = malloc(sizeof(GRAFO));
    g->tam = n;
    g->m = malloc(sizeof(float*)*n);
    if (g->m == NULL ) return NULL;
    for (i=0;i<n;i++) {
        g->m[i] = malloc(sizeof(float)*n);
        if (g->m==NULL) return NULL;
    }
    // aloca lista contigua de pessoas
    g->p = malloc(sizeof(PESSOA*)*n);
    if (g->p==NULL) return NULL;
    // preenche lista contigua de pessoas
    np = lp->ini;
    for (i=0;i<n;i++) {
        g->p[i] = np->p;
        np = np->prox;
    }
    // inicializa matriz de relacoes
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            g->m[i][j] = 0;
        }
    }
    // preenche matriz de relacoes
    nr = lr->ini;
    while (nr!=NULL) {
        icredor = -1;
        idevedor = -1;
        for (i=0;i<n;i++) {
            if ( nr->r->credor == g->p[i] ) {
                icredor = i;
                break;
            }
        }
        for (i=0;i<n;i++) {
            if ( nr->r->devedor == g->p[i] ) {
                idevedor = i;
                break;
            }
        }
        if (icredor!=-1 && idevedor!=-1) {
            g->m[icredor][idevedor]+=nr->r->valor;
        }
        nr=nr->prox;
    }
    for (i=0;i<n;i++) {
        printf(" %8.8s",g->p[i]->login);
    }
    printf("\n");
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            printf(" %8.2f",g->m[j][i]);
        }
        printf("   %s",g->p[i]->login);
        printf("\n");
    }
    return g;
    destroiListaP(lp);
    destroiListaR(lr);
}
void destroiGrafo ( GRAFO *g ) {
    int i;
    if (g==NULL) return;
    for (i=0;i<g->tam;i++) {
        free(g->p[i]);
        free(g->m[i]);
    }
    free (g);
    g=NULL;
}
void saveData (char *fname, ARVORE *a) {
    LISTA_P *lp;
    NODO_P *np;
    LISTA_R *lr;
    NODO_R *nr;
    FILE *f;
    if (fname==NULL || a==NULL) {
        fprintf(stderr,"Erro: nao foi possivel salvar dados.");
        return;
    }
    f = fopen(fname,"w");
    if (f==NULL) {
        fprintf(stderr,"Erro: nao foi possivel salvar dados.");
        return;
    }
    // obtem lista com todas pessoas
    lp= criaListaP();
    percorreArvore( a->filho, lp );
    // obtem lista com todas relacoes
    lr= criaListaR();
    np = lp->ini;
    while ( np!=NULL ) {
        nr=np->p->dividas->ini;
        while ( nr!=NULL ) {
            adicionaR(lr, nr->r);
            nr = nr->prox;
        }
        nr=np->p->emprestimos->ini;
        while ( nr!=NULL ) {
            adicionaR(lr, nr->r);
            nr = nr->prox;
        }
        np=np->prox;
    }
    // modelo de arquivo save
    //
    // [numero de pessoas]
    // [nome 1]
    // [login 1]
    // .
    // .
    // [nome n]
    // [login n]
    // [numero de relacoes]
    // [relacao 1: credor]
    // [relacao 1: devedor]
    // [relacao 1: valor]
    // .
    // .
    // [relacao n: credor]
    // [relacao n: devedor]
    // [relacao n: valor]
    fprintf(f,"%d\n",lp->tam);
    np = lp->ini;
    while (np!=NULL) {
        fprintf(f,"%s\n",np->p->nome);
        fprintf(f,"%s\n",np->p->login);
        np = np->prox;
    }
    fprintf(f,"%d\n",lr->tam);
    nr = lr->ini;
    while (nr!=NULL) {
        fprintf(f,"%s\n",nr->r->credor->login);
        fprintf(f,"%s\n",nr->r->devedor->login);
        fprintf(f,"%.2f\n",nr->r->valor);
        nr = nr->prox;
    }
    destroiListaP(lp);
    destroiListaR(lr);
    fclose(f);
}
void loadData (char *fname, ARVORE *logins, ARVORE *nomes) {
    int n, i, max=500, err;
    char *nome, *login, *lcredor, *ldevedor, *linha;
    float valor;
    FILE *f;
    PESSOA *p;
    RELACAO *r;
    if (fname==NULL || logins==NULL || nomes==NULL) {
        fprintf(stderr,"Erro: nao foi possivel carregar dados\n");
        return;
    }
    f = fopen(fname,"r");
    if (f==NULL) {
        fprintf(stderr,"Erro: nao foi possivel carregar dados\n");
        return;
    }
    nome = malloc(sizeof(char)*max);
    login = malloc(sizeof(char)*max);
    lcredor = malloc(sizeof(char)*max);
    ldevedor = malloc(sizeof(char)*max);
    linha = malloc(sizeof(char)*max);
    fgets(linha,max,f);
    sscanf(linha,"%d",&n);
    for (i=0;i<n;i++) {
        fgets(nome,max,f);
        *(strchr(nome,'\n'))='\0';
        fgets(login,max,f);
        *(strchr(login,'\n'))='\0';
        p=NULL;
        p=criaPessoa(login,nome);
        err = cadastraP( p, logins);
        err+= cadastraP( p, nomes);
        if (err!=0) {
            fprintf(stderr,"Erro: erro ao carregar arquivo");
            return;
        }
    }
    fgets(linha,max,f);
    sscanf(linha,"%d",&n);
    for (i=0;i<n;i++) {
        fgets(lcredor,max,f);
        *(strchr(lcredor,'\n'))='\0';
        fgets(ldevedor,max,f);
        *(strchr(ldevedor,'\n'))='\0';
        fgets(linha,max,f);
        sscanf(linha,"%f",&valor);
        r = NULL;
        r = criaRelacao(
                pesquisaLogin(lcredor,logins),
                pesquisaLogin(ldevedor,logins),
                valor);
    }
    fclose(f);
    free(nome);
    free(login);
    free(lcredor);
    free(ldevedor);
}
