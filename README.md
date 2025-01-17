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
$O(1,44⋅logn)$

### Inserção

A inserção requer, inicialmente, a localização do nó onde a nova chave será inserida, o que é feito recursivamente. Após a inserção, a árvore precisa ser reequilibrada para corrigir possíveis desbalanceamentos. No pior caso, pode ser necessário realizar uma rotação dupla (esquerda-direita ou direita-esquerda). No entanto, no máximo, são necessárias duas rotações [2], cada uma com custo $O(1)$.

Assim, o custo de inserção é proporcional à altura da árvore:
$O(1,44⋅logn(busca) + 2(rotação)) = O(1,44⋅logn)$

### Remoção

A remoção na árvore AVL começa pela localização do nó a ser removido, com custo $O(1,44 \cdot \log{n})$. Após encontrar o nó, existem três casos a serem tratados:

- Nó folha: basta removê-lo diretamente.
- Nó com 1 filho: o filho substitui o pai.
- Nó com 2 filhos: é necessário encontrar o maior nó da subárvore esquerda, substituir o nó a ser removido por este maior nó e, então, removê-lo (essa remoção cairá em um dos dois casos anteriores).

No pior caso, percorremos a altura inteira da árvore ($1,44 \cdot \log{n}$) e realizamos até uma rotação por nível da árvore [2]. Assim, o custo total da operação de remoção no pior caso é:
$O(1,44⋅logn (busca) + 1,44⋅logn(rotações))=O(2,88⋅logn)$

### União

A operação de união é implementada por meio da cópia de árvores. A função percorre uma árvore inteira e insere cada elemento em uma árvore destino (não são permitidos elementos duplicados).

Para uma árvore de tamanho $n$, a cópia tem custo $O(1,44 \cdot n \log{n})$. Se a segunda árvore a ser unida tem tamanho $m$, o custo total da operação de união é:
$O(n(1,44⋅logn)(percorrer A e inserir)+m(1,44⋅log(n+m))(percorrer B e inserir)) = O(1,44(nlogn + mlog(n+m))$

### Interseção

A interseção é realizada percorrendo todos os nós de uma árvore $A$ e verificando, para cada nó, se ele também está presente (busca) em uma segunda árvore $B$. Caso positivo, o nó é inserido na árvore $C$, que representa o resultado da interseção.

Se $A$ tem tamanho $n$, $B$ tem tamanho $m$, e assumimos que $B$ contém $A$, o custo da interseção será:
$O(n(percorrer A)⋅1,44⋅logm(busca em B)⋅1,44⋅logn(inserção em C)) = O(2,07⋅nlogn⋅logm)$

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
4. Número de rotações constante
5. Recálculo das cores dos nós no caminho de inserção

Desse modo, precisamos fazer uma busca e depois as devidos ajustes. Segundo [5], o número máximo de rotações por inserção é constante, embora maior que em uma red black tree normal. Então temos:
$O(2⋅\log{n})$

### Remoção
A remoção na LLRB mantém as propriedades de balanceamento com mecanismos específicos de reequilíbrio.

Estratégias de remoção:
- Remoção de nó folha
- Remoção de nó com um filho
- Remoção de nó com dois filhos (substituição pelo predecessor)
- Rebalanceamento após remoção
- Ajuste de cores para manter as propriedades da árvore

Deste modo, precisamos buscar o nó a ser removido, depois ajustar para manter as propriedades. Agora temos até 2 ajustes que podem ocorrer em cada nível, além da substituição interna se o nó a ser removido não for uma folha que tem complexidade de aproximadamente $O(\log{n})$. Desse modo, a complexidade total fica:
$O(2⋅\log{n}(busca) + 2\log{n}(transformações)) = O(4⋅\log{n})$

### União
A operação de união pode ser implementada percorrendo uma árvore e inserindo seus elementos em outra.

O cálculo da complexidade será semelhante com o da AVL, sendo $n$ o tamanho da primeira árvore e $m$ o custo da segunda, fica:
$O(2⋅(nlogn + mlog(n+m)))$

### Interseção
A interseção realiza uma busca em uma segunda árvore para cada elemento da primeira.

Também, semelhante à AVL, o custo será:
$O(n⋅2⋅log⁡m⋅2⋅logn) = O(4⋅nlogn⋅logm)$

### Comparação com AVL
Diferenças principais em relação à árvore AVL:
- Implementação mais simples
- Pior complexidade quando considerando as constantes
- Tolerância a um nível adicional de desbalanceamento
- Menor sobrecarga de armazenamento (não requer altura explícita, embora precise armazenar as cores)

### Nota
Tentamos análisar a literatura existente para encontrar o número de rotações feito da inserção e remoção da LLRBT, mas aparentemente isso é um tanto complicado. Embora na Red Black normal o número de rotações seja constante, na Left-leaning o número de rotações na remoção parece tem um fator logn (proporcional a altura da árvore). Mas não encontramos muito material discutindo isso, exceto [5]. No final, a complexidade assintótica acaba sendo a mesma e depende da altura, que é maior na LLRBT do que na AVL.

## Referências

- [1] CMU: AVL Trees: https://www.cs.cmu.edu/~rjsimmon/15122-s13/rec/19.pdf
- Arxiv:
  - [2] Amortized rotation cost in AVL trees https://arxiv.org/abs/1506.03528
- Robert Sedgewick:
  - [3] Left-leaning Red-Black Trees: https://sedgewick.io/wp-content/themes/sedgewick/papers/2008LLRB.pdf
  - [4] https://pdfs.semanticscholar.org/80d8/531ce3c7ad5dbf18e659addb71ed3539f395.pdf
- [5] Eddie Kohler (Harvard): https://read.seas.harvard.edu/~kohler/notes/llrb.html
