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

## Árvore Rubro-Negra Inclinada para a Esquerda (Left-Leaning Red-Black Tree)
A árvore rubro-negra inclinada para a esquerda (LLRB) é uma variante da árvore rubro-negra tradicional que simplifica o processo de balanceamento e manutenção da estrutura da árvore. Desenvolvida por Robert Sedgewick, esta estrutura de dados mantém propriedades que garantem um balanceamento eficiente e operações com complexidade logarítmica.

Essa árvore possui algumas propriedades importantes: todos os nós vermelhos são inclinados para a esquerda, não existem nós vermelhos conectados com nós vermelhos, todos os caminhos da raiz para folhas tem o mesmo número de nós pretos e a altura máxima da árvore é $2⋅\log{(n)}$.

### Busca
A operação de busca em uma LLRB segue o mesmo princípio de uma árvore de busca binária padrão, com a garantia de balanceamento. Assim, de acordo com a altura máxima, a busca terá custo:
$O(2⋅\log{n})$

### Inserção
A inserção na LLRB é mais complexa devido às regras de manutenção da cor dos nós e do balanceamento.

Etapas principais:
1. Inserção inicial como em uma árvore de busca binária
2. Coloração do novo nó como vermelho
3. Rebalanceamento através de rotações e recoloração
4. No máximo duas rotações por inserção
5. Recálculo das cores dos nós no caminho de inserção

Desse modo, precisamos fazer uma busca e depois as devidos ajustes. Como podemos ter que fazer até uma Rotação $O(1)$ e uma Inversão $O(1)$ por nível $O(2⋅\log{n})$, o custo total de inserção será:
$O(6⋅\log{n})$

### Remoção
A remoção na LLRB mantém as propriedades de balanceamento com mecanismos específicos de reequilíbrio.

Estratégias de remoção:
- Remoção de nó folha
- Remoção de nó com um filho
- Remoção de nó com dois filhos (substituição pelo predecessor)
- Rebalanceamento após remoção
- Ajuste de cores para manter as propriedades da árvore

Deste modo, precisamos buscar o nó a ser removido, depois ajustar para manter as propriedades. Agora temos 3 ajustes que podem ocorrer em cada nível, além da substituição interna se o a ser removido não for uma folha que tem complexidade de aproximadamente $O(\log{n})$. Desse modo, a complexidade total fica:
$O(9⋅\log{n})$

### União
A operação de união pode ser implementada percorrendo uma árvore e inserindo seus elementos em outra.

O cálculo da complexidade será semelhante com o da AVL, sendo $n$ o tamanho da primeira árvore e $m$ o custo da segunda, fica:
$O(2⋅(nlogn + mlogm))$

### Interseção
A interseção realiza uma busca em uma segunda árvore para cada elemento da primeira.

Também, semelhante à AVL, o custo será:
$O(n⋅2⋅log⁡n⋅2⋅log⁡m)$

### Comparação com AVL
Diferenças principais em relação à árvore AVL:
- Implementação mais simples
- Menos rotações durante inserção/remoção
- Tolerância a um nível adicional de desbalanceamento
- Menor sobrecarga de armazenamento (não requer altura explícita)

## Referências

- CMU: AVL Trees: https://www.cs.cmu.edu/~rjsimmon/15122-s13/rec/19.pdf
- Arxiv:
  - Amortized rotation cost in AVL trees https://arxiv.org/abs/1506.03528
- Robert Sedgewick: Left-leaning Red-Black Trees: https://sedgewick.io/wp-content/themes/sedgewick/papers/2008LLRB.pdf
- Robert Sedgewick: https://pdfs.semanticscholar.org/80d8/531ce3c7ad5dbf18e659addb71ed3539f395.pdf