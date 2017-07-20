## trabalho-final-ed
# Trabalho final da disciplina Estruturas de Dados (INF01126 Turma U) 2017/1

## Como compilar

Este projeto e' compilado com auxilio da ferramenta `make`

Compila programa:
`make` 

Compila e roda o programa imediatamente:
`make run`

Limpa o diretorio de compilacao:
`make clean`

## Como usar o programa
O programa apresenta menus numerados e o usuario seleciona uma opcao
digitando o numero correspondente seguido da tecla enter.

Para compilar, rodar o programa com as entradas de dados definidas
em `inputs.txt`:

```
make check
./wow
```
Selecionar opcao `4. Carregar dados` e carregar arquivo `dados.wow`

### Operacoes implementadas
- [x] Registro de pessoas
- [ ] Desregistro de pessoas
- [x] Dividas de pessoas
- [x] Lista de dividas de um usuario
- [x] Lista de balanco (dividas e emprestimos)
- [x] Vinculos financeiros (grafo)
- [x] Lista de nomes (usuarios com mesmo nome)
- [x] Busca por nome (em arvore de pesquisa)
- [x] Lista das 10 ultimas transacoes
- [x] Salvar e carregar dados

## Estruturas de dados utilizadas

* Tipo PESSOA contem login, nome, lista de dividas e emprestimos
* Tipo RELACAO contem valor da relacao, ponteiro para credor e devedor
* Listas encadeadas com insercao ordenada e deteccao de itens duplicados
  * Lista contem tamanho e ponteiro para o primeiro nodo
  * Nodos da lista tem ponteiro para o proximo item
  * Lista de pessoas (ordenada por login e anti-duplicata)
  * Lista de relacoes (anti-duplicata, em ordem de insercao)
* Arvore de pesquisa
  * Nodos tem como chave um `char`
  * Nodos tem ponteiro para o primeiro irmao
  * Nodos tem ponteiro para o primeiro filho
  * Nodos tem um lista de pessoas
* Lista circular em contiguidade fisica
  * Historico (ultimas 10 transacoes)
* Grafo em matriz de adjacencia

```c
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
    int tam;
} GRAFO;
```
