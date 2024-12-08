# Set

O TAD set foi construído a partir de dois TADs que servem de base para as operações de:
    - Pertencimento
    - União
    - Intersecção
    - Remoção
    - Inserção

O SET só serve para empacotar as operações implementadas nos TADs AVL (árvore 
Adelson-Velsky and Landis) e RBT (árvore Left Leaning Red Black). Essas duas estruturas
de dados podem ser utilizadas pelo usuário do TAD set. A estrutura escolhida é
determinada pelo parametro tipo passado de argumento na função de criação do SET, 
0 indica AVL e 1 indica LLRB. As vantagens e desvantagens dessas duas estruturas 
em relação ao seu uso de base para o conjunto são apresentadas a seguir:


## Árvore AVL (Adeldo-Velsky-Landis)

A árvore AVL é uma árvore binária auto-balanceável que permite operações de 
busca muito rápidas. Um detalhe importante para a análise da performance das operações
feitas na árvore AVL é a sua áltura máxima que determinada por $\frac{1}{log{\phi}}logn$, ou cerca de $1,44 logn$.
