# Tree（樹）

## 1. 定義與基本術語

**Tree（樹）**是一種以「節點（node）」與「邊（edge）」構成的**非線性**資料結構，常用於表示階層（hierarchy）關係。

常見術語：

* **Root（根）**：最上層節點
* **Parent / Child（父/子）**：相鄰的上下層節點
* **Siblings（兄弟節點）**：同一父節點的子節點
* **Leaf（葉節點）**：沒有子節點的節點
* **Internal node（內部節點）**：至少有一個子節點的節點
* **Edge（邊）**：連接兩節點的連線（通常表示父子關係）
* **Subtree（子樹）**：某節點作為根所形成的樹
* **Degree（度）**：

  * 節點度：該節點的子節點數
  * 樹的度：所有節點度的最大值
* **Path（路徑）**：節點序列，連續節點間有邊相連
* **Depth（深度）**：root 到某節點的邊數（root 深度通常為 0）
* **Height（高度）**：某節點到最深葉節點的最長路徑邊數（樹高 = root 高度）
* **Level（層級）**：常以 root 為第 0 層或第 1 層（需明確定義）

樹的常用性質（以 root 深度為 0）：

* 若樹有 `n` 個節點，且為一棵連通、無環的樹，則邊數為 `n - 1`

---

## 2. 樹的表示法（Representation）

### 2.1 指標/參考結構（Linked representation）

每個節點保存其子節點的參考：

* 例如：`children[]`（可變長度）
* 或二元樹保存 `left`、`right`

適合：節點度不固定或樹型多樣。

### 2.2 陣列表示法（常見於 Complete Binary Tree / Heap）

對於**完全二元樹**，可用陣列緊密存放：

* 若以 1-based index：

  * parent(i) = i / 2
  * left(i) = 2i
  * right(i) = 2i + 1
* 若以 0-based index：

  * parent(i) = (i - 1) / 2
  * left(i) = 2i + 1
  * right(i) = 2i + 2

適合：Heap、完全二元樹。

---

## 3. Tree Traversal（走訪）

### 3.1 DFS（Depth-First Traversal，深度優先）

在二元樹中最常見三種：

* **Preorder（前序）**：Root → Left → Right
* **Inorder（中序）**：Left → Root → Right
* **Postorder（後序）**：Left → Right → Root

### 3.2 BFS / Level-order（層序走訪）

* 由上到下、由左到右逐層走訪
* 常用 queue 實作

---

## 4. 常見樹種類（總覽）

以下按「用途/性質」整理常見樹。

---

## 5. General Tree（一般樹 / 多叉樹）

**一般樹**不限制每個節點的子節點數。

特性：

* 節點度可變
* 常見應用：檔案系統目錄樹、組織架構

表示法常見：

* `children` list/vector
* 或「左子右兄（Left-Child Right-Sibling）」轉成二元表示：

  * left 指向第一個子節點
  * right 指向下一個兄弟節點

---

## 6. Binary Tree（二元樹）

**Binary Tree**：每個節點最多兩個子節點（left/right）。

### 6.1 型態分類

* **Full Binary Tree（滿二元樹）**：每個節點要嘛 0 子（葉），要嘛 2 子
* **Complete Binary Tree（完全二元樹）**：除最後一層外全滿，最後一層由左到右填滿
* **Perfect Binary Tree（完美二元樹）**：所有內部節點都有 2 子，且所有葉在同一層（即各層都滿）

常見性質（以 Perfect 二元樹為例）：

* 若高度為 `h`（root 到葉的邊數），節點數 `n = 2^(h+1) - 1`

---

## 7. Binary Search Tree（BST，二元搜尋樹）

### 7.1 定義（BST Ordering Property）

對任一節點 `x`：

* 左子樹所有 key < x.key
* 右子樹所有 key > x.key
  （若允許重複 key，需定義一致的規則，例如等於放右邊）

### 7.2 操作（概念）

* **Search**：沿著比較結果走左/右
* **Insert**：找到空位插入為葉節點
* **Delete**：分三種情況

  1. 刪除葉節點：直接移除
  2. 只有一個子節點：以子節點取代該節點
  3. 有兩個子節點：用 **inorder successor（右子樹最小）**或 **inorder predecessor（左子樹最大）**取代，再刪除被搬移的節點

### 7.3 複雜度（以高度 h 表示）

* Search/Insert/Delete：O(h)
* 若樹退化成鏈狀：h = O(n)
* 若平衡：h = O(log n)

---

## 8. Balanced BST（平衡二元搜尋樹）

平衡樹的目的：限制高度，使操作維持接近 O(log n)。

### 8.1 AVL Tree

**AVL Tree** 是高度嚴格平衡的 BST。

定義：

* 任一節點的左右子樹高度差（balance factor） ∈ { -1, 0, +1 }

維護方式：

* 插入/刪除後，若失衡，透過旋轉恢復平衡：

  * **LL rotation**（右旋）
  * **RR rotation**（左旋）
  * **LR rotation**（先左旋後右旋）
  * **RL rotation**（先右旋後左旋）

特性：

* 高度較低、查找效率佳
* 旋轉較頻繁（相對某些其他平衡樹）

### 8.2 Red-Black Tree（紅黑樹）

**Red-Black Tree** 是較「寬鬆平衡」的 BST。

典型約束（以標準定義）：

* 每個節點是紅或黑
* root 是黑
* 紅節點不能有紅子節點（無連續紅）
* 從任一節點到其所有 NIL 葉的每條路徑，黑節點數相同（black-height 相同）

特性：

* 插入/刪除的重平衡通常較 AVL 少旋轉
* 高度仍維持 O(log n)

---

## 9. Heap（堆積 / 優先佇列常用結構）

**Heap** 通常指 **Binary Heap（二元堆）**：一種基於完全二元樹的結構，滿足 heap property。

### 9.1 Heap Property

* **Min-Heap**：每個節點 key ≤ 子節點 key（root 最小）
* **Max-Heap**：每個節點 key ≥ 子節點 key（root 最大）

### 9.2 典型操作（概念）

* **Insert**：放到最後（維持 complete），再向上調整（heapify-up / sift-up）
* **Extract-Min/Max**：取 root，將最後元素放到 root，再向下調整（heapify-down / sift-down）
* **Build-Heap**：可自底向上 heapify

特性：

* 不是 BST：不支援依 key 的有序走訪（中序不會得到排序）
* 適合：快速取最小/最大元素

---

## 10. Trie（前綴樹 / 字典樹）

**Trie** 用於儲存字串集合（或任何可分解為符號序列的 key），節點表示「前綴」。

### 10.1 結構

* root 表示空字串
* 每條邊代表一個字元（或 token）
* 節點通常有：

  * children（對應下一個字元的分支）
  * end-of-word flag（此節點是否為某字串結尾）

### 10.2 特性

* 查找字串是否存在：按字元逐層走
* 可高效支援：

  * prefix query（查某前綴下有哪些字）
  * autocomplete（自動完成）

成本特徵（以字串長度 L）：

* 插入/查找通常與 L 成正比（不直接依 n）

空間特徵：

* 可能較大（許多節點與分支），常配合壓縮技巧（見 Radix/Patricia）

---

## 11. B-Tree / B+ Tree（多路搜尋樹，常見於資料庫與檔案系統）

目的：降低磁碟/頁面 I/O 次數，透過「高分支度」降低高度。

### 11.1 B-Tree（概念）

* 每個節點可存多個 key 與多個 child 指標
* 節點內 key 保持排序
* 所有葉通常在同一層（高度一致）
* 插入刪除透過 split/merge/redistribute 維持節點 key 數量在範圍內

### 11.2 B+ Tree（概念）

* 所有實際資料（record 或指向 record 的指標）都放在 **leaf**
* 內部節點只存 key 作為索引
* leaf 之間通常有 linked list 指標（便於 range scan）

差異要點：

* B+ Tree 對範圍查詢（range query）通常更有效率（可沿 leaf linked list 連續掃描）

---

## 12. Segment Tree（線段樹）

用於對陣列做**區間查詢**與（可能的）**區間更新**。

### 12.1 概念

* 將區間遞迴切半形成樹
* 每個節點代表一段區間，存放該區間的聚合資訊（例如 sum/min/max/gcd）

### 12.2 特性（以長度 n）

* 樹高：O(log n)
* 單次區間查詢：O(log n)
* 單點更新：O(log n)
* 若加入 lazy propagation，可支援區間更新並維持 O(log n)

---

## 13. Fenwick Tree（Binary Indexed Tree, BIT）

用於維護前綴聚合（常見為 prefix sum）與單點更新。

### 13.1 特性

* update：O(log n)
* prefix query：O(log n)
* 空間：O(n)
* 實作通常以陣列 + lowbit（最低位元）運算

BIT 與 Segment Tree 的差異：

* BIT 結構更精簡，適合前綴/區間和類型的聚合（可用差分做區間）
* Segment Tree 更通用，可支援更廣泛的區間操作

---

## 14. Tree 的選用

* 需要 key 有序且支援搜尋/插入/刪除：BST / 平衡 BST
* 需要快速取得全域最小/最大：Heap
* 需要字串前綴查詢：Trie
* 需要外存（磁碟）友好、降低高度：B-Tree / B+ Tree
* 需要區間查詢/更新：Segment Tree / BIT
* 需要表示一般階層關係：General Tree

---

## 15. 名詞對照

* **Binary Tree**：二元樹
* **BST**：二元搜尋樹
* **Balanced BST**：平衡二元搜尋樹
* **AVL / Red-Black**：常見平衡 BST 類型
* **Heap**：堆積（完全二元樹 + heap property）
* **Trie**：前綴樹
* **B-Tree / B+ Tree**：多路搜尋樹（外存索引）
* **Segment Tree**：線段樹
* **Fenwick Tree / BIT**：二元索引樹

---
