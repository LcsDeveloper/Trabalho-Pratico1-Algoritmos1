# Trabalho-Pratico1-Algoritmos1

# Introdução

Ana e Bernardo, dois amigos, foram juntos a um festival de música que contava com diversas barracas de comida. Ana decidiu experimentar os doces caseiros, enquanto Bernardo preferiu os sabores salgados. Entretanto, uma chuva repentina assolou o festival, transformando a experiência em uma grande correria por cobertura. Por sorte, dentro do festival havia espalhados diversos guarda-sóis que serviram como abrigo. Ana e Bernardo conseguiram ficar a salvos, e sob nenhuma circunstância estavam dispostos a se molhar. A partir dessa situação, três problemas foram levantados:

1. **Problema 1**: Sabendo que somente é possível passar de um abrigo para outro se e somente se eles têm espaços em comum (ou seja, ao menos um ponto em comum), determinar se Ana e Bernardo podem se encontrar e, caso possível, calcular o número mínimo de abrigos que eles devem atravessar para isso.
2. **Problema 2**: Considerando que as pessoas sempre andam buscando percorrer as menores distâncias, determinar o maior número de abrigos que uma pessoa qualquer teria de percorrer para atravessar o festival após a chuva ter começado.
3. **Problema 3**: Determinar o número de abrigos críticos, ou seja, abrigos que, se removidos após o início da chuva, tornariam alguns abrigos inacessíveis a partir de outros.

Tendo em mente as questões levantadas, é prático que o problema possa ser observado de forma que ferramentas conhecidas possam ser utilizadas. Para isso, o problema foi modelado como um grafo.

# Modelagem

A situação é modelada como um grafo não direcionado $G = (V,E)$, onde:
- $V$: conjunto de vértices, cada um representando um abrigo.
- $E$: conjunto de arestas, onde uma aresta $(u,v)$ existe se os abrigos $u$ e $v$ têm interseção (i.e., a distância entre seus centros é $\leq$ soma dos raios).

De tal maneira, a partir de $G$, reduzimos cada problema à:

1. **Problema 1**: Encontrar o caminho mais curto entre dois vértices em $G$, resolvido com BFS.
2. **Problema 2**: Calcular o diâmetro de $G$, que pode ser obtido a partir dos caminhos mais longos entre todos os pares de vértices.
3. **Problema 3**: Identificar vértices de articulação, que podem ser mapeados usando o Algoritmo de Tarjan.

Computacionalmente, o grafo foi representado como um vetor de listas, seguindo o conceito da representação por lista de adjacência.

# Solução

## Problema 1

Seja $v$ vértice de $G$, e $BFS(v)$ uma função que retorna um vetor de distâncias $D=[d_1,d_2,…,d_{|V|}]$, onde $d_i$ é a distância de $v$ a $v_i$, $\forall v_i \in V$, e seja também $v_a,v_b \in V$ os vértices iniciais de Ana e Bernardo. A solução obtida via $BFS$ a partir de $v_a$ segue os seguintes passos:

- Inicialize um vetor $D$ com $D[v_i]=0$, $\forall v_i \in V$.
- Execute $BFS$, atualizando $D[v]$ para cada vértice $v$ visitado.
- Se $v_b$ não for visitado, retorne $-1$. Caso contrário, retorne $D[v_b]$.

**Prova**: Como o $BFS$ visita todos os vértices alcançáveis a partir de $v_a$ em ordem de distância crescente, a primeira ocorrência de $v_b$ na fila garante que $D[b]$ é a distância mínima. Se $v_b$ não for visitado, o grafo é desconexo.

### Implementação
A função `shortestPath(v_a, v_b)` implementa o $BFS$ com otimização para interromper a busca quando $v_b$ é encontrado, reduzindo o tempo de execução em casos favoráveis.

## Problema 2

O diâmetro de um dado grafo não ponderado e não orientado pode ser definido como:

**Definição**: Seja $G=(V,E)$ um grafo não orientado e não ponderado. O diâmetro de $G$ é definido como a maior distância mínima entre todos os pares de vértices distintos do grafo. Se $G$ for desconexo, o diâmetro é o maior diâmetro entre suas componentes conexas.

Tendo em mente a definição de diâmetro, e sendo $G_i$ o i-ésimo sub-grafo conexo de $G$, podemos procurar uma solução da seguinte forma:

- Para cada $G_i$ faça:
  - Execute $BFS$ a partir de um vértice arbitrário $v$. Seja $u$ o vértice mais distante de $v$.
  - Execute $BFS$ a partir de $u$. Seja $w$ o vértice mais distante de $u$.
  - Guarde a distância entre $u$ e $w$.
- Retorne a maior distância encontrada.

**Prova**: Seja $u$ o vértice mais distante de um vértice arbitrário $v$. Como o $BFS$ encontra caminhos mais curtos, $u$ deve ser um extremo do diâmetro. Executar $BFS$ a partir de $u$ encontra o vértice $w$ mais distante, cuja distância é o diâmetro. Caso contrário, existiria um caminho mais longo não detectado, contradizendo a propriedade do $BFS$.

### Implementação
A implementação utiliza a função `sizePaths(i)`, que executa $BFS$ a partir de um vértice e retorna um vetor de distâncias, e `greatestPath()`, que calcula o maior caminho em todas as componentes conexas.

## Problema 3

Vértices de articulação são definidos como:

**Definição**: Seja $v$ vértice de $G$, e seja também $K(G)$ o número de componentes conexos em $G$. $v$ é definido como vértice de articulação se e somente se $K(G - \{v\}) > K(G)$.

A solução utiliza uma $DFS$ modificada para identificar vértices de articulação:

- Para cada $G_i$ faça:
  - Execute $DFS$ a partir de um vértice arbitrário.
  - Compute os valores de `time` (tempo de descoberta) e `low` (menor tempo alcançável).
  - Verifique as condições de articulação:
    - $v$ é raiz da MST e tem dois ou mais filhos.
    - Para algum filho $v_c$ de $v$, $low(v_c) \geq time(v)$.
- Retorne todos os vértices de articulação.

### Implementação
As funções `DFStree(i)` e `cutNodes()` implementam a $DFS$ modificada e verificam as condições para vértices de articulação.

# Análise de Complexidade

## Problema 1
- **Tempo**: $O(V + E)$ (BFS padrão).
- **Espaço**: $O(V)$ (vetores auxiliares).

## Problema 2
- **Tempo**: $O(V(V + E))$ (BFS para cada componente conexa).
- **Espaço**: $O(V)$.

## Problema 3
- **Tempo**: $O(V + E)$ (DFS modificada).
- **Espaço**: $O(V)$.

# Considerações Finais
A implementação seguiu a modelagem proposta com otimizações como interrupção antecipada do BFS e cálculo eficiente de vértices de articulação. O uso de listas de adjacência mostrou-se ideal para grafos esparsos.

# Referências
- Cormen, T. H. *Introduction to Algorithms*. MIT Press, 2009.
- Kleinberg, J.; Tardos, É. *Algorithm Design*. Pearson, 2005.
- [GeeksforGeeks: Articulation Points](https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/)
