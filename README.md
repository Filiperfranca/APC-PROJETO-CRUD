# 🏦 JARVIS BANK

> Sistema bancário em linguagem C com interface via terminal, assistido pelo JARVIS.

---

## 📋 Índice

- [Sobre o Projeto](#sobre-o-projeto)
- [Funcionalidades](#funcionalidades)
- [Pré-requisitos](#pré-requisitos)
- [Como Compilar](#como-compilar)
- [Como Usar](#como-usar)
- [Menu Principal](#menu-principal)
- [Estrutura do Código](#estrutura-do-código)
- [Limitações Conhecidas](#limitações-conhecidas)
- [Roteiro de Testes](#roteiro-de-testes)
- [Autor](#autor)

---

## Sobre o Projeto

**JARVIS BANK** é um sistema bancário simulado desenvolvido inteiramente em C, executado via terminal. Ao iniciar, o usuário cria um perfil com nome e passa a interagir com o assistente **JARVIS**, que guia todas as operações financeiras: depósitos, saques, transferências, consultas e edição de histórico.

O projeto foi desenvolvido com foco em aprendizado de estruturas em C (`struct`, `enum`, arrays), manipulação de entrada/saída e lógica de validação robusta.

---

## Funcionalidades

| Funcionalidade | Descrição |
|---|---|
| ✅ Cadastro de usuário | Nome personalizado salvo na sessão |
| ✅ Depósito | Adiciona valor ao saldo com registro no extrato |
| ✅ Saque | Retira valor do saldo com validação de saldo disponível |
| ✅ Transferência | Transfere valor para um destino nomeado |
| ✅ Consulta de saldo e extrato | Exibe saldo atual e histórico completo de transações |
| ✅ Pesquisa por ID | Busca uma transação específica pelo seu ID |
| ✅ Edição de transação | Altera valor e/ou destino de qualquer transação registrada |
| ✅ Exclusão de registro | Remove uma transação do extrato (sem reverter o saldo) |
| ✅ Validação de inputs | Trata entradas inválidas, valores zerados e overflow |

---

## Pré-requisitos

- Compilador C compatível com **C99 ou superior** (ex: GCC, Clang)
- Terminal (Linux, macOS ou Windows com MinGW/WSL)

---

## Como Compilar

```bash
gcc banco.c -o banco -lm
```

> A flag `-lm` é necessária por conta do uso de `math.h` (função `fabs`).

Para compilar com avisos ativados (recomendado):

```bash
gcc banco.c -o banco -lm -Wall -Wextra -std=c99
```

---

## Como Usar

Após compilar, execute:

```bash
./banco
```

Na inicialização, o JARVIS solicitará seu nome de usuário. Em seguida, o menu principal estará disponível.

---

## Menu Principal

```
==========
  BANCO
==========

1- CONSULTAR SALDO/EXTRATO
2- DEPOSITAR VALOR
3- SACAR VALOR
4- TRANSFERIR VALOR
5- EDITAR TRANSFERENCIA
6- PESQUISAR TRANSFERENCIA
7- SAIR
```

### Detalhes de cada opção

**1 - Consultar Saldo/Extrato**
Exibe o saldo atual e, se houver transações, o extrato completo no formato:
```
ID    TIPO             VALOR      DESTINO
0     DEPOSITO         1000.00    João
1     TRANSFERENCIA    300.00     Maria
```

**2 - Depositar**
Solicita um valor positivo e o adiciona ao saldo. O depósito é registrado no extrato com destino igual ao nome do usuário.

**3 - Sacar**
Solicita um valor e o desconta do saldo, desde que haja saldo suficiente.

**4 - Transferir**
Solicita o nome do destinatário e o valor. A transação é registrada como `TRANSFERENCIA`.

**5 - Editar Transação**
Solicita o ID da transação e abre um submenu:
- `1 - EDITAR`: altera o valor (e o destino, no caso de transferências)
- `2 - APAGAR`: remove o registro do extrato *(sem reverter o efeito no saldo)*
- `3 - VOLTAR`: retorna ao menu principal

> ⚠️ Apagar um registro não desfaz a movimentação financeira. Para reverter um saque ou transferência, edite o valor para `0` antes de apagar, ou realize a operação inversa manualmente.

**6 - Pesquisar Transação**
Localiza e exibe uma transação específica pelo seu ID.

**7 - Sair**
Encerra o sistema.

---

## Estrutura do Código

```
banco.c
│
├── Enums
│   ├── transacao     → DEPOSITO, SAQUE, TRANSFERENCIA
│   └── menu          → opções do menu principal (1–7)
│
├── Structs
│   ├── historico     → id, tipo, valor, destino[51]
│   └── user          → nome[51], saldo, extrato[999]
│
└── main()
    ├── Cadastro do usuário
    └── Loop do menu principal
        ├── case CONSULTAR_S
        ├── case DEPOSITAR
        ├── case SACAR
        ├── case TRANSFERIR
        ├── case EDITAR_T  →  submenu (EDITAR / APAGAR / VOLTAR)
        ├── case PESQUISAR
        └── case SAIR
```

---

## Limitações Conhecidas

| Limitação | Descrição |
|---|---|
| Sem persistência | Todos os dados são perdidos ao encerrar o programa |
| Apenas um usuário | O sistema suporta somente uma conta por sessão |
| Máximo de 999 transações | Limite fixo definido em tempo de compilação |
| Sem criptografia | Nenhuma camada de segurança nos dados |
| IDs não reutilizados | Ao apagar uma transação, o ID dela não é reaproveitado |

---

## Roteiro de Testes

Sequência sugerida para validar todas as funcionalidades:

```
1.  Nome: João
2.  Depositar: 1000        → saldo: 1000.00
3.  Depositar: 500         → saldo: 1500.00
4.  Consultar              → extrato com 2 transações (ID 0 e 1)
5.  Sacar: 200             → saldo: 1300.00
6.  Transferir: Maria/300  → saldo: 1000.00
7.  Transferir: Pedro/1500 → SALDO INSUFICIENTE
8.  Editar ID 0 → valor 800   → saldo: 800.00
9.  Editar ID 3 → valor 100, destino Ana → saldo: 1000.00
10. Pesquisar ID 2         → exibe saque de 200
11. Pesquisar ID 99        → não registrado
12. Depositar: 0           → rejeitado
13. Sacar: -50             → tratado como 50 (fabs)
14. Digitar "abc" no menu  → OPÇÃO INVÁLIDA
15. Apagar ID 1            → consultar e confirmar remoção
```

---

## Autor

Desenvolvido como projeto de estudo em C.

Contribuições, sugestões e issues são bem-vindas!