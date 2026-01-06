# Stack（堆疊）筆記

## 1. 定義與核心概念

**Stack（堆疊）**是一種**線性資料結構**，遵循 **LIFO（Last In, First Out；後進先出）** 的存取規則：

* 最後放入（push）的元素，會最先被取出（pop）。
* 所有插入與刪除操作都集中在同一端，稱為 **top（堆疊頂端）**。

---

## 2. 抽象資料型別（ADT）與介面

Stack 通常被視為一種 **ADT（Abstract Data Type）**，定義「能做哪些操作」而非「如何實作」。

常見操作：

* `push(x)`：把元素 `x` 放到 top
* `pop()`：移除並回傳 top 元素
* `top()` / `peek()`：回傳 top 元素但不移除
* `isEmpty()`：判斷是否為空
* `size()`：回傳元素數量（若介面提供）

---

## 3. 基本操作行為（語意）

假設堆疊內容由底到頂為：`[a, b, c]`（top = c）

* `push(d)` 後：`[a, b, c, d]`
* `top()`：回傳 `d`（堆疊不變）
* `pop()`：回傳並移除 `d`，堆疊變回 `[a, b, c]`

---

## 4. 實作方式

Stack 可用多種方式實作，主要差異在於底層儲存結構。

### 4.1 Array-based Stack（以陣列實作）

以陣列 `arr` 儲存元素，並用整數 `topIndex`（或 `top`）記錄頂端位置。

典型狀態定義：

* 空堆疊：`topIndex = -1`
* top 元素位置：`arr[topIndex]`

操作概念：

* `push(x)`：`topIndex++`，`arr[topIndex] = x`
* `pop()`：取 `arr[topIndex]`，`topIndex--`
* `peek()`：回傳 `arr[topIndex]`

**容量（capacity）**：

* 若為固定大小陣列，超出容量需處理 overflow
* 若採動態陣列，可在滿時擴容（resize）

### 4.2 Linked-list Stack（以鏈結串列實作）

以 linked list 的 head 作為 top，讓操作集中在 head 端以獲得 O(1) 性能。

操作概念：

* `push(x)`：在 head 前插入新節點
* `pop()`：刪除 head 節點並回傳其值
* `peek()`：回傳 head 的值

---

## 5. 時間與空間複雜度

令 n 為元素數量。

| 操作         |              Array-based |      Linked-list |
| ---------- | -----------------------: | ---------------: |
| `push`     | O(1)（動態擴容時可能有一次 O(n) 搬移） |             O(1) |
| `pop`      |                     O(1) |             O(1) |
| `peek/top` |                     O(1) |             O(1) |
| `isEmpty`  |                     O(1) |             O(1) |
| 空間         |                     O(n) | O(n)（每個節點另含指標開銷） |

---

## 6. 邊界條件與錯誤處理

### 6.1 Underflow（下溢）

對**空堆疊**呼叫 `pop()` 或 `peek()`。

常見處理方式：

* 回傳錯誤碼 / `null`
* 丟出例外（exception）
* 由呼叫端先用 `isEmpty()` 檢查

### 6.2 Overflow（上溢）

對**固定容量**堆疊進行 `push()` 且已滿。

常見處理方式：

* 回傳錯誤碼 / 丟出例外
* 若允許動態擴容：配置更大容量並搬移資料

---

## 7. 常見變形與延伸結構

### 7.1 Min Stack（支援取最小值）

在一般 stack 的基礎上，額外維護一個結構，使得能在 **O(1)** 取得目前堆疊內的最小值。

常見做法：

* 另維護一個「最小值堆疊」同步 push/pop
* 或在每個節點存「到此為止的最小值」

介面例：

* `getMin()`：回傳當前最小值（不移除）

### 7.2 Bounded Stack（有容量上限）

* 明確定義 `capacity`
* `push` 前先檢查是否已滿

---

## 8. 典型應用場景（概念層面）

### 8.1 呼叫堆疊（Call Stack）

* 用於管理函式呼叫與返回：

  * 儲存返回位址
  * 儲存區域變數、暫存器狀態等
* 遞迴（recursion）會逐層 push stack frame，返回時 pop

### 8.2 括號匹配（Delimiter Matching）

* 逐字掃描字串
* 遇到左括號 push，遇到右括號檢查 top 是否為對應左括號並 pop
* 最終 stack 應為空才代表完全匹配

### 8.3 表達式處理（Expression Processing）

* 中序轉後序（infix → postfix）
* 後序（postfix）計算
* 運算子優先序與括號結構可用 stack 管理

### 8.4 反轉序列

* push 所有元素，再逐一 pop 取出，即可得到反序

### 8.5 Undo / Backtracking 概念

* 把狀態或操作記錄 push 進去
* 需要回退時 pop 還原

---

## 9. 實作重點

### 9.1 Stack 的不變量（Invariant）

設計時常維持以下不變量：

* top 永遠指向「最後插入且尚未移除」的元素
* 空堆疊時：

  * array-based：`topIndex` 指向一個明確的空狀態（如 -1）
  * list-based：`head = null`

### 9.2 介面行為一致性

* `pop()` 是否回傳值或只移除
* 空堆疊時的行為（例外、回傳特殊值）需一致且文件化

---

## 10. 操作範例

從空堆疊開始（右側為 top）：

1. 初始：`[]`
2. `push(10)` → `[10]`
3. `push(20)` → `[10, 20]`
4. `peek()` → 回傳 `20`，堆疊不變 `[10, 20]`
5. `pop()` → 回傳 `20`，堆疊變 `[10]`
6. `pop()` → 回傳 `10`，堆疊變 `[]`
7. `isEmpty()` → `true`
