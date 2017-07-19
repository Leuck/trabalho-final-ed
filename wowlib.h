/*
 * Ricardo Frederico Leuck Filho
 * TRABALHO FINAL - ESTRUTURAS DE DADOS 2017/1
 * ARQUIVO HEADER - WOWLIB
 */

#ifndef WOWLIB
#define WOWLIB

// TIPO PESSOA
typedef struct pessoa_st {
	char *login, *nome;
	struct lista_relacao_st *dividas, *emprestimos;
	struct lista_pessoas_st *amigos;
} PESSOA;
// TIPO RELACAO (DIVIDA)
typedef struct relacao_st {
	float valor;
	PESSOA *devedor, *credor;
} RELACAO;
// LISTA ENCADEADA DE PESSOAS
typedef struct nodo_pessoa_st {
	PESSOA *p;
	struct nodo_pessoa_st *prox;
} NODO_P;
typedef struct lista_pessoas_st {
	NODO_P *ini;
	int tam;
} LISTA_P;
// LISTA ENCADEADA DE DIVIDAS
typedef struct nodo_relacao_st {
	RELACAO *r;
	struct nodo_relacao_st *prox;
} NODO_R;
typedef struct lista_relacao_st {
	NODO_R *ini;
	int tam;
} LISTA_R;
// ARVORE DE PESQUISA DE NOMES
typedef struct arvore_pesquisa_st {
	char chave;
	LISTA_P *l;
	struct arvore_pesquisa_st *irmao, *filho;
} NODO_A;
typedef struct raiz_st {
	NODO_A *filho; //primeiro filho
	char t; //arvore de [l]ogins ou [n]omes
} ARVORE;

// PROTOTIPOS DE FUNCOES
PESSOA * criaPessoa(char *login, char *nome);
LISTA_P * criaListaP();
void destroiListaP(LISTA_P *l);
void imprimeListaP(LISTA_P *l);
void adicionaP(LISTA_P *l, PESSOA *p);
void removeP(LISTA_P *l, char *login);
LISTA_R * criaListaR();
void destroiListaR(LISTA_R *l);
void adicionaR(LISTA_R *l, RELACAO *r);
RELACAO * criaRelacao(PESSOA *credor, PESSOA *devedor, float valor);
void imprimeListaR(LISTA_R *l);
ARVORE * criaArvore(char t);
NODO_A * criaNodoA(char chave);
LISTA_P * percorreArvore( NODO_A *raiz, LISTA_P *l );
NODO_A * inserePessoaNaArvore( char *nome, NODO_A *raiz);
int cadastraP(PESSOA *p, ARVORE *a);
NODO_A * pesquisaNaArvore (char *nome, NODO_A *raiz);
LISTA_P * pesquisaArvore(char *nome, char tipo, ARVORE *a);
PESSOA * pesquisaLogin(char *login, ARVORE *a);
char * lerstring ();

#endif
