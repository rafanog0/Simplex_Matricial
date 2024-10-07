# Implementação do Algoritmo Simplex em C

## Introdução

Este projeto apresenta uma implementação do algoritmo Simplex (apenas maximização) em linguagem C, destinada a resolver problemas de programação linear. Esse repositorio é destinado para a disciplina "Modelos e Algoritmos de Otimização" do curso de Ciência da Computação no IDP-DF.

## Como o Programa Recebe Entradas

O programa lê os dados de entrada a partir da entrada padrão (stdin). As entradas devem ser fornecidas em um formato específico para que o algoritmo possa processá-las corretamente. A estrutura geral das entradas é a seguinte:

1. **Número de Variáveis e Restrições:**

   ```plaintext
   <número_de_variáveis> <número_de_restrições>
   ```

2. **Coeficientes da Função Objetivo:**

   ```plaintext
   <coeficiente1> <coeficiente2> ... <coeficienteN>
   ```

3. **Restrições:**

   Para cada restrição, forneça:

   - **Coeficientes das Variáveis:**

     ```plaintext
     <coeficiente1> <coeficiente2> ... <coeficienteN>
     ```

   - **Valor do Lado Direito da Restrição:**

     ```plaintext
     <valor>
     ```

   Repita este passo para cada restrição.

---

### Exemplo de Entrada

Considere o seguinte exemplo de entrada para um problema com 3 variáveis e 2 restrições:

```plaintext
3 2
5 4 3
2 3 1
5
4 1 2
11
```

**Explicação:**

- **Linha 1:** `3 2` indica que o problema possui 3 variáveis e 2 restrições.
- **Linha 2:** `5 4 3` são os coeficientes da função objetivo a ser maximizada: Z = 5x₁ + 4x₂ + 3x₃.
- **Linha 3 e 4:** `2 3 1` e `5` representam a primeira restrição: 2x₁ + 3x₂ + x₃ ≤ 5.
- **Linha 5 e 6:** `4 1 2` e `11` representam a segunda restrição: 4x₁ + x₂ + 2x₃ ≤ 11.

---

## Como Utilizar o Makefile

O `Makefile` fornecido simplifica o processo de compilação e execução do programa, permitindo que você compile e execute o código com facilidade, além de utilizar arquivos de entrada específicos localizados no diretório `inputs/`.

### Passos para Utilização:

1. **Adicionar Arquivos de Entrada:**

   Coloque seus arquivos de entrada dentro do diretório `inputs/`. Cada arquivo deve conter os dados de entrada conforme o formato especificado anteriormente.

   Exemplo de como adicionar um arquivo de entrada chamado `entrada1`:

   - Crie o arquivo `inputs/entrada1`.
   - Insira os dados do problema no arquivo, seguindo o formato correto.

2. **Compilar o Programa:**

   Para compilar o programa, execute:

   ```bash
   make compile
   ```

   Este comando compila os arquivos fonte e gera o executável `simplex`.

3. **Executar o Programa com um Arquivo de Entrada:**

   Para executar o programa utilizando um arquivo de entrada específico, use o seguinte comando:

   ```bash
   make entradaXY
   ```

   Substitua `entradaXY` pelo nome do arquivo de entrada que você deseja utilizar (sem o caminho `inputs/`).


   As entradas de exemplos seguem o seguinte padrão:


   `X -> Número de Variáveis`
   
   `Y -> Número de Restrições`

   **Exemplo:**

   ```bash
   make entrada22
   ```

   Este comando executa o programa com o arquivo `inputs/entrada22` como entrada.

4. **Compilar e Executar em Sequência:**

   Para compilar e executar o programa de uma só vez, você pode utilizar:

   ```bash
   make all
   ```

   Este comando irá compilar o programa (se necessário) e executar o executável gerado.

5. **Limpar os Arquivos Compilados:**

   Para remover os arquivos objetos e o executável, liberando espaço ou preparando para uma compilação limpa, utilize:

   ```bash
   make clean
   ```
