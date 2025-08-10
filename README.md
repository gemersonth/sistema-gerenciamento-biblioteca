# Sistema de Gerenciamento de Biblioteca

Um sistema criado em linguagem C para otimizar o gerenciamento de livros em uma biblioteca. 
O sistema permite adicionar e removar livros da biblioteca, permite listar livros, alugar livro,  
devolver livro, aumentar o prazo de devolução e realizar o pagamento de multas, caso houver alguma. 


## Funcionalidades:

* **ADICIONAR LIVRO:** Essa função permite adicionar livros a biblioteca, apenas com a permissão do administrador (admin123).

* **REMOVER LIVRO:** Essa função permite remover livros da biblioteca, assim como a função adicionar livro, requer a permissão do administrador (admin123).

* **LISTAR LIVROS:** Essa função permite listar todos os livros presentes na biblioteca, caso não tiver algum, irá mostrar um campo vazio.

* **ALOCAR LIVRO:** Essa função permite o locador alugar um livro, se disponível na biblioteca, não estiver locado por outra pessoa e não tiver nenhum livro locado em seu nome.

* **DEVOLVER LIVRO:** Essa função permite que o locador devolva o livro a biblioteca, deixando disponível para outra pessoa alugar. Caso o locador devolva o livro fora do prazo não poderá devolver até que pague uma multa.

* **AUMENTAR PRAZO:** Essa função serve para aumentar o prazo de devolução do livro, ela irá verificar se há multa no nome do locador. Caso houver não poderá aumentar o prazo, terá que pagar a multa primeiro.

* **PAGAR:** Essa função permite realizar o pagamento das multas do locador.

## Requisitos Funcionais:

1. Todas as funções com exceção da função ADICIONAR LIVRO fazem uma verificação para saber se há livros ou não na biblioteca.
2. Apenas as funções de ADICIONAR E REMOVER LIVRO são de acesso exclusivo do administrador.
3. Para alugar um livro, o locador não pode ter nenhum outro livro locado em seu nome.
4. Para devolver o livro, o locador precisa fornecer o nome e a quantidade de dias que ele está com o livro. Caso ele tenha ultrapassado o prazo, o sistema irá calcular uma multa referente a quantidade de dias ultrapassados, e não poderá devolver até que pague a multa.
5. Para aumentar o prazo, o locador não pode ter multas em seu nome.

## Requisitos Não Funcionais:

1. Usabilidade: Sistema simples e fácil de usar, com um menu/painel simples.
2. Segurança: Sistema seguro, com algumas funcionalidades exclusivas para o administrador.
3. Velocidade: Sistema rápido e versátil.
4. Escalabilidade: Sistema escalável, com suporte a quantidade pequena, média e grande de usuários.

## Regras de Negócio:

O sistema possui um valor/taxa constante de R$ 0.50 que é multiplicado pela quantidade de dias a mais do prazo de entrega do livro. 
Então se o usuário alugou um livro por 15 dias, e devolveu em 20 dias (5 dias a mais), o sistema irá calcular uma multa com base na taxa e quantidades de dias ultrapassados.

<br>

## EXECUTAR SCRIPT

Compilar e executar no **WINDOWS**

    gcc main.c -o main.exe

    ./main.exe

Compilar e executar no **LINUX**

    gcc main.c -o main

    ./main