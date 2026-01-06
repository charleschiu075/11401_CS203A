# Queue（佇列）筆記

## 1. 定義與核心概念

**Queue（佇列）**是一種**線性資料結構**，遵循 **FIFO（First In, First Out；先進先出）** 的存取規則：

* 最先加入（enqueue）的元素，會最先被移除（dequeue）。
* 插入與刪除發生在不同端：

  * **rear / back（尾端）**：加入元素
  * **front（前端）**：移除元素

---

## 2. 抽象資料型別（ADT）與介面

Queue 通常以 **ADT（Abstract Data Type）** 形式定義操作語意，而不綁定特定實作。

常見操作：

* `enqueue(x)`：把元素 `x` 加入隊尾（rear）
* `dequeue()`：移除並回傳隊首（front）元素
* `front()` / `peek()`：回傳隊首元素但不移除
* `isEmpty()`：判斷是否為空
* `size()`：回傳元素數量（若介面提供）

---

## 3. 基本操作行為（語意）

假設隊列內容由 front 到 rear 為：`[a, b, c]`

* `enqueue(d)` 後：`[a, b, c, d]`
* `front()`：回傳 `a`（隊列不變）
* `dequeue()`：回傳並移除 `a`，隊列變為 `[b, c, d]`

---

## 4. 實作方式

### 4.1 Array-based Queue（陣列實作）

#### 4.1.1 直接位移（不建議）

* 用陣列存放元素
* `dequeue` 後把所有元素左移一格維持 front 在 index 0
* 缺點：`dequeue` 需要搬移，時間 O(n)

#### 4.1.2 Circular Buffer（環狀陣列 / Ring Buffer）

最常見的陣列實作方式，避免搬移。

核心概念：

* 使用固定容量 `capacity`
* 維護兩個索引：

  * `frontIndex`：指向隊首元素位置
  * `rearIndex`：指向「下一個可插入位置」或指向隊尾（視定義）
* 索引以 mod 運算循環：

  * `next(i) = (i + 1) % capacity`

常見狀態表示（兩種典型設計）：

**A. 用 size 表示空/滿（推薦語意清晰）**

* `size = 0` → empty
* `size = capacity` → full

**B. 留一格空間區分空/滿**

* empty：`frontIndex == rearIndex`
* full：`(rearIndex + 1) % capacity == frontIndex`
* 實際可存元素數量為 `capacity - 1`

操作概念（以「用 size」為例）：

* `enqueue(x)`：

  * `arr[rearIndex] = x`
  * `rearIndex = (rearIndex + 1) % capacity`
  * `size++`
* `dequeue()`：

  * `x = arr[frontIndex]`
  * `frontIndex = (frontIndex + 1) % capacity`
  * `size--`

---

### 4.2 Linked-list Queue（鏈結串列實作）

通常維護兩個指標：

* `head` 指向 front
* `tail` 指向 rear

操作概念：

* `enqueue(x)`：在 tail 後插入新節點並更新 tail（O(1)）
* `dequeue()`：刪除 head 並更新 head（O(1)）
* 若刪到空（head 變 null），tail 也必須設為 null

---

## 5. 時間與空間複雜度

令 n 為元素數量。

| 操作           |      Circular Array Queue | Linked-list Queue |
| ------------ | ------------------------: | ----------------: |
| `enqueue`    |                      O(1) |              O(1) |
| `dequeue`    |                      O(1) |              O(1) |
| `front/peek` |                      O(1) |              O(1) |
| `isEmpty`    |                      O(1) |              O(1) |
| 空間           | O(capacity) 或 O(n)（動態擴容時） |     O(n)（含節點指標開銷） |

---

## 6. 邊界條件與錯誤處理

### 6.1 Underflow（下溢）

對空佇列執行 `dequeue()` 或 `front()`。

常見處理方式：

* 回傳錯誤碼 / `null`
* 丟出例外（exception）
* 呼叫端先用 `isEmpty()` 檢查

### 6.2 Overflow（上溢）

對固定容量（環狀陣列）佇列在滿狀態執行 `enqueue()`。

常見處理方式：

* 回傳錯誤碼 / 丟出例外
* 若允許動態擴容：建立更大陣列並重新排列元素（常保留 FIFO 順序）

---

## 7. Queue 的常見變形

### 7.1 Deque（Double-Ended Queue，雙端佇列）

支援兩端都可插入/刪除：

* `pushFront`, `pushBack`, `popFront`, `popBack`
  常用於：
* 滑動視窗（需兩端操作）
* 模擬某些排程結構

### 7.2 Priority Queue（優先佇列）

取出順序不是 FIFO，而是依優先級（例如最小/最大 key）決定。

* 常用實作：binary heap
* 主要操作：`push`, `pop`, `top`

### 7.3 Blocking Queue（阻塞佇列）

多用於並行/多執行緒情境：

* 空時 `dequeue` 會等待
* 滿時 `enqueue` 會等待
  需要同步機制（mutex/condition variable 等）支援

---

## 8. 典型應用場景（概念層面）

### 8.1 緩衝（Buffering）

* I/O 緩衝、網路封包緩衝
* 生產者（producer）放入資料，消費者（consumer）取出

### 8.2 任務排程（Scheduling）

* 以 FIFO 排隊處理請求或工作
* 例如列印工作、事件迴圈（event loop）中的待處理事件序列（視實作而定）

### 8.3 圖/樹的層序走訪（Level-order traversal）

* BFS（Breadth-First Search）使用 queue：

  * 先把起點 enqueue
  * 重複 dequeue 一個節點並 enqueue 其鄰居

---

## 9. 實作設計重點（不涉及語言細節）

### 9.1 Invariant（不變量）

正確的 queue 實作通常維持：

* 佇列順序永遠符合 FIFO
* `front` 總是指向「下一個要被 dequeue 的元素」
* `rear` 總是指向「下一個要被 enqueue 的位置」或「最後一個元素」（依定義一致即可）
* 在環狀陣列中，每次移動索引都必須做 `mod capacity`

### 9.2 空與滿的判定必須一致

* 若用 `size` 判定空/滿：程式碼清晰，較少歧義
* 若用索引相等判定：需明確保留一格或另設旗標，否則 `front==rear` 會同時對應空與滿造成混淆

---

## 10. 操作範例

從空佇列開始（由 front → rear）：

1. 初始：`[]`
2. `enqueue(10)` → `[10]`
3. `enqueue(20)` → `[10, 20]`
4. `enqueue(30)` → `[10, 20, 30]`
5. `front()` → 回傳 `10`，佇列不變 `[10, 20, 30]`
6. `dequeue()` → 回傳 `10`，佇列變 `[20, 30]`
7. `dequeue()` → 回傳 `20`，佇列變 `[30]`
8. `dequeue()` → 回傳 `30`，佇列變 `[]`
9. `isEmpty()` → `true`
