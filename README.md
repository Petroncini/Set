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
feitas na árvore AVL é a sua áltura máxima que determinada por $\frac{1}{log{\phi}}logn$, 
ou cerca de $1,44\cdot logn$.

Outro fato importante é que em nossa implementação, utilizamos structs para os nós da árvore
que armazenam um inteiro representando a altura desse nó. Dito isso podemos encontrar o custo 
de cada operação sobre a árvore avl.

### Busca

O custo da operação de busca na árvore avl é determinada pela áltura máxima da árvore, pois
para cada nível da árvore precisamos fazer uma única comparação.
Então, o custo de busca é de $O(1,44 \cdot logn)$

### Inserção

Na inserção, precisamos primeiro encontrar o nó onde faremos a inserção, isso feito recursivamente.
Depois da inserção, é preciso fazer o rebalancemaneto da árvore para lidar com qualquer possível desbalanceamento
criado pela inserção. O pior caso é o de ser necessário realizar uma rotação esquerda-direita ou 
direita esquerda na árvore. Mas no máximo, somente duas rotações de custo $O(1)$ são necessárias por
inserção.
Além das rotações, é necessário atualizar a altura de cada nó, mas isso é feito na volta da recursão da inserção
já que só precisamos olhar para os nós filhos de cada nó para calcular sua altura. 

Então, o custo de inserção na árvore AVL é proporcional a sua altura, e é então
$O(1,44\cdot logn)$

### Remoção

A remoção na árvore AVL também depende inicialmente de encontrarmos o nó a ser removido em temo
$O(1,44 \cdot logn)$. Mas depois do nó ser encontrado temos que lidar com os dois casos do nó a 
ser removido ter 0, 1 ou 2 filhos. Se ele tiver 0 filhos (nó folha), é só tirar ele da árvore.
Se tiver 1 filho esse filho é puxado pra cima e substitui o pai. 

No entanto, se o nó tiver 2 filhos, é necessário encontrar o maior nó em sua sub-árvore esquerda,
substituir o nó a ser removido por esse máximo esquerdo e então remover este. Essa segunda remoção
caira em um dos dois casos anteriores, pois o máximo esquerdo necessáriamente não tem um filho direito.

Assim, no pior caso da remoção, ou removemos um nó folha ou trocamos um nó no meio da árvore por um 
nó folha filho dele. De qualquer forma, percorremos a altura inteira da árvore qe é no máximo $1,44\cdot logn$.
Um detalhe importante da remoção é, diferente da inserção, ela pode precisa de até uma rotação por nível da árvore.
Então no pior caso, a remoção terá custo na ordem de $O(1,44\cdot logn) + O(1,44\cdot logn) = O(2,88\cdot logn)$.

### União

A criação de um set união é feita através de uma função de cópia de árvores. Essa função percorre uma ávore inteira 
e insere cada um de seus elementos em uma árvore destinho (note: a árvore como implementada não admite elementos
repetidos). Então, para uma árvore de tamanho $n$ o custo dessa cópia será de $O(1,44\cdot nlogn)$. Uma segunda
árvore é copiada no set destino para formar a união. Se essa ávore tem custo $m$ temos então um custo totals de operação
de $O(1,44\cdot (nlogn + mlogm))$

### Interseção

A criação de um set interseção é feita através de uma função que percorre todos os nós uma árvore A e os insere
em uma árvore C somente se o elemento estiver presente (busca) em uma árvore B. Se A for de tamanho n, B for de tamanho $m$,
e digamos que o conjunto B contém o conjunto A, o custo da operação de intersecção será de $O(n\cdot 1,44 logn \cdot 1,44 logm)$



















## Referências
    - https://www.cs.cmu.edu/~rjsimmon/15122-s13/rec/19.pdf
    - https://arxiv.org/abs/1506.03528
