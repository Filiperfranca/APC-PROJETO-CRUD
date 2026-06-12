# 🏦 JARVIS Bank — Sistema Bancário em C

> Trabalho acadêmico desenvolvido para a disciplina de Programação — implementação de um sistema CRUD completo em linguagem C, com interface interativa via terminal.

---

## 👤 Autor

| Nome | GitHub |
|------|--------|
| Filipe França | [@filipefranca](https://github.com/Filiperfranca/) |

---

## 🎯 Objetivo

Implementar um sistema de cadastro bancário que permita **inserir, consultar, atualizar e remover** registros de transações financeiras, aplicando os conceitos de structs, vetores, enums, estruturas de decisão e repetição em linguagem C.

---

## 🧩 Funcionalidades

### Menu Principal

```
==========
  BANCO
==========

1- CONSULTAR SALDO/EXTRATO
2- DEPOSITAR VALOR
3- SACAR VALOR
4- TRANSFERIR VALOR
5- EDITAR TRANSAÇÃO
6- PESQUISAR TRANSAÇÃO
7- SAIR
```

### Operações disponíveis (CRUD)

| Operação | Descrição |
|----------|-----------|
| **Cadastrar** | Registra depósitos, saques e transferências com ID único |
| **Listar** | Exibe o extrato completo com todas as transações e saldo atual |
| **Buscar** | Pesquisa uma transação específica pelo ID |
| **Atualizar** | Edita o valor e/ou destino de uma transação existente, revertendo o impacto no saldo automaticamente |
| **Remover** | Apaga o registro do extrato mantendo a consistência do vetor |

---

## 🗂️ Estrutura do Código

O projeto foi implementado **exclusivamente dentro da função `main()`**, conforme requisito da disciplina, com organização lógica feita por meio de `switch`, `while` e `do-while`.

### Tipos de dados utilizados

```c
// Enum de tipo de transação
typedef enum { DEPOSITO, SAQUE, TRANSFERENCIA } transacao;

// Struct de cada registro no extrato
typedef struct {
    int id;
    transacao tipo;
    double valor;
    char destino[51];
} historico;

// Struct do usuário
typedef struct {
    char nome[51];
    double saldo;
    historico extrato[999]; // vetor de até 999 transações
} user;
```

### Controle de registros

- `id_transacao` — quantidade atual de transações cadastradas
- `proximo_id` — ID único auto-incrementado para cada nova transação
- Remoção mantém consistência do vetor via shift dos elementos

---

## ✅ Validações implementadas

- Nome de usuário não pode ser vazio
- Valores de depósito, saque e transferência devem ser maiores que zero
- Saldo insuficiente é detectado antes de executar saque ou transferência
- Overflow de saldo é verificado contra `DBL_MAX`
- Entradas não numéricas no menu são tratadas sem travar o programa
- IDs inexistentes retornam mensagem de erro clara
- Limite de 999 transações é verificado antes de cada cadastro

---

## ⚙️ Como compilar e executar

### Pré-requisitos

- GCC instalado (`gcc --version` para verificar)
- Sistema operacional: Linux, macOS ou Windows (com MinGW)

### Compilação

```bash
gcc -o jarvis_bank main.c -lm
```

> A flag `-lm` é necessária para linkar a biblioteca `math.h` (usada pela função `fabs()`).

### Execução

```bash
./jarvis_bank
```

No Windows:
```bash
jarvis_bank.exe
```

---

## 🧪 Roteiro de testes sugerido

| Passo | Ação | Resultado esperado |
|-------|------|--------------------|
| 1 | Depositar `1000` | Saldo: 1000.00 |
| 2 | Depositar `500` | Saldo: 1500.00 |
| 3 | Sacar `200` | Saldo: 1300.00 |
| 4 | Transferir `300` para `Maria` | Saldo: 1000.00 |
| 5 | Transferir `1500` para `Pedro` | SALDO INSUFICIENTE |
| 6 | Pesquisar ID `2` | Exibe o saque de 200 |
| 7 | Pesquisar ID `99` | Transação não registrada |
| 8 | Editar ID `0`, novo valor `800` | Saldo ajustado automaticamente |
| 9 | Apagar ID `1` | Registro removido do extrato |
| 10 | Digitar `abc` no menu | OPÇÃO INVÁLIDA, programa continua |

---

## 📁 Estrutura do repositório

```
📦 jarvis-bank/
├── main.c        # Código-fonte completo
└── README.md     # Documentação do projeto
```

---

## 📋 Requisitos atendidos

- [x] Código exclusivamente na função `main()`
- [x] Menu interativo com opções numéricas
- [x] Programa permanece em execução até o usuário sair
- [x] CRUD completo: cadastrar, listar, buscar, atualizar e remover
- [x] Identificador único validado automaticamente (auto-incremento)
- [x] Todas as entradas validadas
- [x] Uso de `struct` personalizada
- [x] Vetor de estruturas com controle de quantidade de registros
- [x] Remoção mantém consistência do vetor

---

## 📜 Licença

Projeto acadêmico — uso educacional.