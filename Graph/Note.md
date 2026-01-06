# Graph（圖）

## 1. 定義與核心概念

**Graph（圖）**是一種由 **Vertex / Node（頂點/節點）** 與 **Edge（邊）** 構成的資料結構，用來描述「物件之間的關係」。

表示為：

* `G = (V, E)`

  * `V`：頂點集合
  * `E`：邊集合（連結頂點的關係）

圖不必具備階層，也不必連通；可包含環，也可不包含。

---

## 2. 圖的分類

### 2.1 無向圖 vs 有向圖

* **Undirected Graph（無向圖）**：邊沒有方向
  邊可表示為 `{u, v}`
* **Directed Graph（有向圖 / Digraph）**：邊有方向
  邊可表示為 `(u, v)`，代表 `u → v`

### 2.2 加權圖 vs 非加權圖

* **Weighted Graph（加權圖）**：每條邊有權重 `w(e)`（距離、成本、容量等）
* **Unweighted Graph（非加權圖）**：邊沒有權重（可視為權重皆為 1）

### 2.3 簡單圖、多重邊、自環

* **Simple Graph（簡單圖）**：不含自環、不含多重邊
* **Multigraph（多重圖）**：允許同一對頂點間有多條邊
* **Self-loop（自環）**：邊從頂點連回自身

### 2.4 連通性（Connectivity）

* **Connected（連通）**（無向圖）：任兩點間存在路徑
* **Connected Components（連通分量）**：無向圖中每個最大連通子圖
* **Strongly Connected（強連通）**（有向圖）：任兩點 u、v 皆互相可達
* **Strongly Connected Components（SCC）**：有向圖的強連通分量
* **Weakly Connected（弱連通）**：有向圖忽略方向後連通

### 2.5 特殊圖型

* **DAG（Directed Acyclic Graph）**：有向無環圖
* **Tree（樹）**：連通且無環的無向圖（邊數 = n - 1）
* **Bipartite Graph（二分圖）**：頂點可分成兩群，所有邊只跨群連接
* **Complete Graph（完全圖）**：任兩頂點都有邊相連（無向為 `K_n`）

---

## 3. 基本術語

* **Adjacent（相鄰）**：兩頂點之間有邊
* **Neighbor（鄰居）**：與某頂點相鄰的頂點
* **Degree（度）**（無向圖）：與頂點相連的邊數
* **In-degree / Out-degree（入度/出度）**（有向圖）：

  * 入度：指向該頂點的邊數
  * 出度：由該頂點指出的邊數
* **Path（路徑）**：一串頂點序列，序列中相鄰頂點間皆有邊
* **Simple Path（簡單路徑）**：路徑中頂點不重複
* **Cycle（環）**：起點與終點相同的路徑（通常長度 ≥ 1）
* **Length（長度）**：

  * 非加權：邊數
  * 加權：邊權重總和
* **Distance（距離）**：最短路徑的長度
* **Subgraph（子圖）**：由部分頂點與部分邊構成的圖

---

## 4. 圖的表示法（Graph Representation）

令 `n = |V|`、`m = |E|`。

### 4.1 Adjacency Matrix（鄰接矩陣）

* `n × n` 矩陣 `A`
* 無向圖：`A[u][v] = A[v][u] = 1`（或權重）
* 有向圖：`A[u][v] = 1` 表示 `u → v`

特性：

* 空間：O(n²)
* 查詢是否有邊：O(1)
* 列出某點鄰居：O(n)

適合：圖很密（dense）或需要 O(1) 查邊。

### 4.2 Adjacency List（鄰接串列）

* 每個頂點存一個 list，列出其相鄰頂點（或邊）

特性：

* 空間：O(n + m)
* 查詢是否有邊：平均需掃鄰居（非 O(1)）
* 列出某點鄰居：O(deg(v))

適合：圖很稀疏（sparse），實務最常用。

### 4.3 Edge List（邊列表）

* 直接存所有邊 `(u, v)`（以及可能的權重）

特性：

* 空間：O(m)
* 適合用於某些演算法（如 Kruskal 需要邊排序）

---

## 5. 走訪（Traversal）

### 5.1 BFS（Breadth-First Search，廣度優先）

概念：

* 從起點開始，先走完「同一層距離」的所有節點再往外擴展
* 使用 queue

性質（非加權圖）：

* BFS 會找到起點到各點的**最短路徑（以邊數計）**

時間複雜度：

* Adjacency list：O(n + m)
* Adjacency matrix：O(n²)

### 5.2 DFS（Depth-First Search，深度優先）

概念：

* 沿一條路徑走到底再回溯
* 可用 recursion 或 stack

用途（語意層面）：

* 偵測環（cycle detection）
* 找連通分量
* 拓撲排序（DAG）
* SCC（與其他技巧結合）

時間複雜度：

* Adjacency list：O(n + m)

---

## 6. 最短路徑（Shortest Path）

### 6.1 非加權圖

* 使用 BFS：從單一源點到所有點的最短邊數距離

### 6.2 加權圖（權重非負）

* **Dijkstra**

  * 求單一源點到所有點的最短路徑
  * 常用 priority queue（min-heap）
  * 時間複雜度取決於實作（概念上常用 O((n + m) log n)）

### 6.3 允許負權重（但無負環）

* **Bellman-Ford**

  * 可偵測負環
  * 時間 O(n·m)

### 6.4 全點對最短路徑（All-Pairs）

* **Floyd–Warshall**

  * DP 方式，時間 O(n³)，空間 O(n²)
  * 適合 n 較小且需要所有點對距離

---

## 7. 最小生成樹（Minimum Spanning Tree, MST）

適用於**加權無向連通圖**：找一棵連通所有頂點、邊權重總和最小的樹。

性質：

* MST 有 `n - 1` 條邊
* 若權重皆不同，MST 唯一（常見性質）

常見方法：

* **Kruskal**

  * 邊排序後依序加入（避免形成環）
  * 需用 Union-Find（Disjoint Set Union, DSU）判斷是否成環
* **Prim**

  * 從某點開始逐步擴張，總是選擇跨越 cut 的最小權重邊
  * 常用 priority queue

---

## 8. 拓撲排序（Topological Sort）

適用於 **DAG（有向無環圖）**：給出一個頂點順序，使每條邊 `u → v` 都滿足 `u` 在 `v` 之前。

常見方法：

* **Kahn’s Algorithm（入度法）**

  * 計算每點入度
  * 將入度為 0 的點入 queue
  * 取出後移除其出邊並更新入度
* **DFS-based**

  * DFS 完成時間的逆序（finish time reverse order）

若圖有環，拓撲排序不存在。

---

## 9. Union-Find（Disjoint Set Union, DSU）

用於維護集合的合併與查詢是否同集合，常在：

* Kruskal MST
* 連通性問題（離線合併）

操作：

* `find(x)`：找代表元
* `union(a, b)`：合併兩集合

典型優化：

* Path compression（路徑壓縮）
* Union by rank/size（按秩/大小合併）

---

## 10. 二分圖（Bipartite Graph）

定義：

* 頂點可分為兩集合 U、V
* 每條邊必跨集合連接（不允許同集合內連邊）

判定（概念）：

* 可用 BFS/DFS 進行 2-coloring（兩色染色）
* 若存在奇數長度環（odd cycle），則不是二分圖

---

## 11. 有向圖的強連通分量（SCC）

**SCC（Strongly Connected Component）**：在有向圖中，任兩點互相可達的最大子集合。

常見方法（名稱層面）：

* **Kosaraju**

  * 需要反向圖與兩次 DFS
* **Tarjan**

  * 單次 DFS 搭配 stack 與 low-link 值

用途：

* 將有向圖壓縮成 DAG（SCC condensation graph）

---

## 12. Cut / Bridge / Articulation Point（無向圖結構性概念）

### 12.1 Bridge（橋）

* 移除該邊會使圖的連通分量數增加

### 12.2 Articulation Point（割點）

* 移除該頂點會使圖的連通分量數增加

這些概念通常透過 DFS 的時間戳與 low 值來判定（概念層面）。

---

## 13. 圖的輸入與建模觀點

常見建模方式：

* 物件 → 頂點（例如城市、使用者、頁面、狀態）
* 關係/可達 → 邊（例如道路、追蹤關係、超連結、狀態轉移）
* 成本/距離/時間 → 邊權重
* 限制方向性 → 有向邊
* 限制互斥集合 → 二分圖

---

## 14. 名詞對照

* Vertex/Node：頂點/節點
* Edge：邊
* Directed/Undirected：有向/無向
* Weighted：加權
* Path/Cycle：路徑/環
* Connected Components：連通分量
* SCC：強連通分量
* DAG：有向無環圖
* BFS/DFS：廣度/深度優先
* Shortest Path：最短路徑
* MST：最小生成樹
* Topological Sort：拓撲排序
* DSU/Union-Find：並查集

---
