# Set

O TAD Set foi construído a partir de dois TADs que servem de base para as operações de:

- Pertencimento
- União
- Interseção
- Remoção
- Inserção

O Set é apenas uma camada que empacota as operações implementadas nos TADs AVL (Árvore Adelson-Velsky and Landis) e RBT (Árvore Left-Leaning Red-Black). Essas duas estruturas de dados estão disponíveis para o usuário do TAD Set. A estrutura escolhida é determinada pelo parâmetro tipo passado como argumento na função de criação do Set:

- 0 indica AVL
- 1 indica LLRB

As vantagens e desvantagens dessas estruturas em relação ao seu uso como base para o conjunto são discutidas a seguir:

## Árvore AVL (Adelson-Velsky-Landis)

A árvore AVL é uma árvore binária auto-balanceável que proporciona operações de busca muito eficientes. Um ponto relevante para analisar o desempenho das operações na árvore AVL é a sua altura máxima, que é limitada por $\frac{1}{\log{\phi}} \log{n}$, $\phi$ sendo a razão áurea, ou aproximadamente $1,44 \cdot \log{n}$.

Na nossa implementação, os nós da árvore são representados por structs que armazenam, entre outras informações, um inteiro que indica a altura do nó. Com isso, podemos determinar o custo de cada operação na árvore AVL.

### Busca

O custo da operação de busca é limitado pela altura máxima da árvore, pois a cada nível é feita apenas uma comparação. Assim, o custo de busca é:
$O(1,44⋅log⁡n)$

### Inserção

A inserção requer, inicialmente, a localização do nó onde a nova chave será inserida, o que é feito recursivamente. Após a inserção, a árvore precisa ser reequilibrada para corrigir possíveis desbalanceamentos. No pior caso, pode ser necessário realizar uma rotação dupla (esquerda-direita ou direita-esquerda). No entanto, no máximo, são necessárias duas rotações, cada uma com custo $O(1)$.

Além disso, a altura de cada nó é recalculada durante o retorno da recursão, sendo necessário apenas consultar os nós filhos.

Assim, o custo de inserção é proporcional à altura da árvore:
$O(1,44⋅log⁡n)$

### Remoção

A remoção na árvore AVL começa pela localização do nó a ser removido, com custo $O(1,44 \cdot \log{n})$. Após encontrar o nó, existem três casos a serem tratados:

- Nó folha: basta removê-lo diretamente.
- Nó com 1 filho: o filho substitui o pai.
- Nó com 2 filhos: é necessário encontrar o maior nó da subárvore esquerda, substituir o nó a ser removido por este maior nó e, então, removê-lo (essa remoção cairá em um dos dois casos anteriores).

No pior caso, percorremos a altura inteira da árvore ($1,44 \cdot \log{n}$) e realizamos até uma rotação por nível da árvore. Assim, o custo total da operação de remoção no pior caso é:
$O(1,44⋅log⁡n)+O(1,44⋅log⁡n)=O(2,88⋅log⁡n)$

### União

A operação de união é implementada por meio da cópia de árvores. A função percorre uma árvore inteira e insere cada elemento em uma árvore destino (não são permitidos elementos duplicados).

Para uma árvore de tamanho $n$, a cópia tem custo $O(1,44 \cdot n \log{n})$. Se a segunda árvore a ser unida tem tamanho $m$, o custo total da operação de união é:
$O(1,44⋅(nlog⁡n+mlog⁡m))$

### Interseção

A interseção é realizada percorrendo todos os nós de uma árvore $A$ e verificando, para cada nó, se ele também está presente (busca) em uma segunda árvore $B$. Caso positivo, o nó é inserido na árvore $C$, que representa o resultado da interseção.

Se $A$ tem tamanho $n$, $B$ tem tamanho $m$, e assumimos que $B$ contém $A$, o custo da interseção será:
$O(n⋅1,44⋅log⁡n⋅1,44⋅log⁡m)$

## Referências

- CMU: AVL Trees: https://www.cs.cmu.edu/~rjsimmon/15122-s13/rec/19.pdf
- Arxiv: Amortized rotation cost in AVL trees https://arxiv.org/abs/1506.03528
