# Heap（堆積）

## 1. 定義與核心概念

**Heap（堆積）**在資料結構脈絡中通常指 **Binary Heap（二元堆）**：
一種以**完全二元樹（Complete Binary Tree）**為形狀約束的結構，並滿足特定的**堆積性質（Heap Property）**，以支援快速取得極值（最小或最大）。

### 1.1 兩種常見 Heap

* **Min-Heap（最小堆）**：任一節點的 key ≤ 其子節點的 key
  ⇒ root 是全體最小值
* **Max-Heap（最大堆）**：任一節點的 key ≥ 其子節點的 key
  ⇒ root 是全體最大值

### 1.2 重要澄清：Heap 不是 BST

Heap 只保證「父子之間」的大小關係（heap property），**不保證整體有序**。
因此：

* 中序走訪不會得到排序結果
* 搜尋任意 key 一般需要 O(n)

---

## 2. 結構性質：完全二元樹（Shape Property）

Binary heap 的形狀必須是**完全二元樹**：

* 除了最後一層外，每層都滿
* 最後一層從左到右依序填滿

此性質使 heap 能用陣列緊密存放，且高度為 **O(log n)**。

---

## 3. 表示法：Array Representation（陣列表示）

令 heap 使用陣列 `A` 儲存，常見有兩種索引風格。

### 3.1 0-based index（常見於多數語言）

* parent(i) = (i - 1) // 2
* left(i) = 2i + 1
* right(i) = 2i + 2

### 3.2 1-based index（教材常見）

* parent(i) = i // 2
* left(i) = 2i
* right(i) = 2i + 1

---

## 4. 基本操作（ADT 行為）

典型 heap 作為優先佇列（Priority Queue）的操作：

* `top()`：回傳 root（min-heap 回傳最小、max-heap 回傳最大）
* `insert(x)`：插入元素
* `extractTop()`：移除並回傳 root
* `size()` / `isEmpty()`

---

## 5. 維護 Heap Property 的基本調整

### 5.1 Sift Up / Heapify Up（上濾）

用途：插入新元素後恢復 heap property。

概念（以 min-heap）：

1. 新元素先放到陣列尾端（維持 complete 形狀）
2. 與 parent 比較，若小於 parent，交換
3. 重複直到 root 或不再違反 heap property

### 5.2 Sift Down / Heapify Down（下濾）

用途：刪除 root（extract）後恢復 heap property。

概念（以 min-heap）：

1. 將最後元素搬到 root
2. root 與兩個子節點比較，與較小的子節點交換（min-heap）
3. 重複直到葉節點或不再違反 heap property

---

## 6. 操作流程與時間複雜度

令 n 為元素數量，heap 高度為 O(log n)。

### 6.1 `top()`

* 直接取 `A[0]`（0-based）或 `A[1]`（1-based）
* **時間：O(1)**

### 6.2 `insert(x)`

* 尾端插入 + sift up
* sift up 最多上移高度次
* **時間：O(log n)**

### 6.3 `extractTop()`

* 取 root、尾端元素補 root + sift down
* sift down 最多下移高度次
* **時間：O(log n)**

### 6.4 `buildHeap`（由陣列建立 heap）

若已給一個無序陣列，建立 heap 的典型方式是「自底向上」對所有非葉節點做 sift down。

* **時間：O(n)**（不是 O(n log n)）
* 直觀原因：靠近底部的節點高度小，下濾成本低，總和可攤平為線性

---

## 7. 常見延伸操作

### 7.1 Increase/Decrease Key（調整鍵值）

* **DecreaseKey（min-heap）**：值變小可能破壞與 parent 的關係 ⇒ sift up
* **IncreaseKey（min-heap）**：值變大可能破壞與 children 的關係 ⇒ sift down
  （max-heap 則方向相反）

### 7.2 Delete arbitrary element（刪除任意位置元素）

常見做法：

1. 把該位置元素與最後元素交換
2. 移除最後元素（等於刪除）
3. 依新值與 parent/children 關係選擇 sift up 或 sift down

---

## 8. Heap 與 Priority Queue 的關係

**Priority Queue（優先佇列）**是一種抽象介面：可快速取得（並移除）最高優先級元素。
Binary heap 是其最常見的實作之一。

* Min-heap ⇒ 最小值優先佇列
* Max-heap ⇒ 最大值優先佇列

---

## 9. 常見 Heap 變形

### 9.1 d-ary Heap（d 元堆）

每個節點有 d 個子節點（d > 2）：

* 高度更低（log_d n）
* 插入上濾時 parent 少，可能更快
* 下濾時要在 d 個子節點中挑最小/最大，單步成本增加

### 9.2 Binomial Heap / Fibonacci Heap（名稱與定位）

這些是更進階的 heap 結構，通常用於特定情境下改善某些操作的攤提成本（例如 decrease-key）。
概念上仍服務於優先佇列，但結構與二元堆不同。

---

## 10. 邊界條件與實作重點

* 空 heap：

  * `top()` / `extractTop()` 需要明確定義行為（回傳特殊值或錯誤/例外）
* 單元素 heap：

  * `extractTop()` 後 heap 變空，索引與 size 更新要一致
* `siftDown` 的比較策略（min-heap）：

  * 必須與「較小的子節點」交換，才能維持 heap property
* 完全二元樹形狀維持：

  * 插入只能放尾端
  * 刪除 root 通常以尾端補位

---

## 11. Heap Sort（堆積排序）概念

Heap sort 以 heap 達成排序：

* 使用 max-heap：每次取最大放到陣列尾端
* 或使用 min-heap：每次取最小形成遞增序列（需額外輸出或覆寫策略）

典型（就地排序）流程（以 max-heap）：

1. build max-heap（O(n)）
2. 重複把 root（最大）與最後元素交換，縮小 heap 範圍，再 sift down
3. 直到完成

性質：

* 時間：O(n log n)
* 額外空間：可做到 O(1)（就地）
* 不穩定排序（不保證相等元素相對次序）

---

## 12. 名詞對照

* Heap：堆積
* Binary Heap：二元堆
* Min-Heap / Max-Heap：最小堆 / 最大堆
* Heap Property：堆積性質（父子關係）
* Complete Binary Tree：完全二元樹（形狀約束）
* Sift Up / Heapify Up：上濾
* Sift Down / Heapify Down：下濾
* Build Heap：建堆
* Extract Top：取出並移除 root（extract-min / extract-max）
* Priority Queue：優先佇列
