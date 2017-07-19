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
// LISTA DE TRASACOES RECENTES
typedef struct recentes_st {
    RELACAO *dados[10];
    int ini, fin, tam;
} RECENTES;
// GRAFO DE VINCULOS FINANCEIROS
typedef struct grafo_st {
    float **m;
    PESSOA **p;
} GRAFO;

// PROTOTIPOS DE FUNCOES
// PESSOAS
PESSOA * criaPessoa (char *login, char *nome);
// LISTA ENCADEADA DE PESSOAS
LISTA_P * criaListaP ();
void destroiListaP (LISTA_P *l);
void imprimeListaP (LISTA_P *l);
void adicionaP (LISTA_P *l, PESSOA *p);
void removeP (LISTA_P *l, char *login);
// LISTA ENCADEADA DE DIVIDAS
LISTA_R * criaListaR ();
void destroiListaR (LISTA_R *l);
void adicionaR (LISTA_R *l, RELACAO *r);
void removeR (RELACAO *r);
RELACAO * criaRelacao (PESSOA *credor, PESSOA *devedor, float valor);
void imprimeListaR (LISTA_R *l);
// ARVORE DE PESQUISA DE NOMES
ARVORE * criaArvore (char t);
NODO_A * criaNodoA (char chave);
LISTA_P * percorreArvore ( NODO_A *raiz, LISTA_P *l );
NODO_A * inserePessoaNaArvore ( char *nome, NODO_A *raiz);
int cadastraP (PESSOA *p, ARVORE *a);
NODO_A * pesquisaNodoArvore (char *nome, NODO_A *raiz);
LISTA_P * pesquisaArvore (char *nome, char tipo, ARVORE *a);
PESSOA * pesquisaLogin (char *login, ARVORE *a);
char * lerstring ();
// LISTA DE TRASACOES RECENTES
RECENTES * inicializaTR ();
void lembrar ( RELACAO *r, RECENTES *l );
RELACAO * acessaHist ( RECENTES *l, int pos );
void imprimeHist ( RECENTES *l );
// GRAFO DE VINCULOS FINANCEIROS
GRAFO * geraGrafo (ARVORE *a);

#endif
