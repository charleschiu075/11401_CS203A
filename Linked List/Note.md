# Linked List（鏈結串列）

## 1. 定義與核心概念

**Linked List（鏈結串列）**是一種線性資料結構，由一個個 **node（節點）**組成。每個節點包含：

* **data / value（資料）**
* **pointer / reference（指標/參考）**：指向下一個節點（或前一個節點）

特性重點：

* 節點在記憶體中**不需要連續**（non-contiguous）
* 透過指標串接形成序列
* **不支援 O(1) 隨機存取**：要訪問第 i 個元素需從頭走訪

---

## 2. Node 結構與記憶體模型

### 2.1 單向節點（Singly Node）

```
[data | next] -> [data | next] -> [data | next] -> null
```

* `next` 指向下一個節點
* 最後一個節點 `next = null`

### 2.2 記憶體特性

* 節點通常分散在 heap（動態記憶體）
* 每次新增節點多半是動態配置（malloc/new）
* 優點：大小可彈性變動
* 缺點：指標跳轉造成 cache locality 差（相對 array 慢）

---

## 3. Linked List 類型

### 3.1 Singly Linked List（單向鏈結串列）

* 每個節點只知道下一個節點
* 優點：節點開銷小（只存一個 next）
* 缺點：無法 O(1) 往回走

### 3.2 Doubly Linked List（雙向鏈結串列）

```
null <- [prev | data | next] <-> [prev | data | next] <-> ... -> null
```

* 每個節點存 `prev` 與 `next`
* 優點：可雙向走訪、刪除某節點更方便
* 缺點：節點額外記憶體成本、操作要維護兩個指標更容易出錯

### 3.3 Circular Linked List（環狀鏈結串列）

* 最後一個節點指回頭（或尾端指向 head）
* 常用於 round-robin、循環排程等

---

## 4. 基本操作與時間複雜度

令 n 為長度。

| 操作                      | 說明                           | 時間複雜度                                  |
| ----------------------- | ---------------------------- | -------------------------------------- |
| Access / Read by index  | 取第 i 個元素                     | **O(n)**                               |
| Search                  | 找某值                          | **O(n)**                               |
| Insert at head          | 頭插                           | **O(1)**                               |
| Delete at head          | 刪頭                           | **O(1)**                               |
| Insert at tail          | 尾插                           | **O(n)**（若無 tail 指標）/ **O(1)**（有 tail） |
| Delete at tail          | 刪尾                           | **O(n)**（需找前一個）                        |
| Insert/Delete at middle | 已知前一節點（singly）或已知該節點（doubly） | **O(1)**（不含定位成本）                       |
| 定位某位置                   | 走訪定位                         | **O(n)**                               |

關鍵理解：

> Linked list 的強項在「指標改接」很快，但定位通常要走訪。

---

## 5. 常見操作細節（指標更新）

以下用 singly linked list 。

### 5.1 在頭部插入（Push Front）

步驟：

1. new node `x`
2. `x.next = head`
3. `head = x`

時間：O(1)

### 5.2 在頭部刪除（Pop Front）

步驟：

1. `tmp = head`
2. `head = head.next`
3. free/delete `tmp`

時間：O(1)

### 5.3 在某節點後插入（Insert After prev）

假設已知 `prev` 節點：

1. new node `x`
2. `x.next = prev.next`
3. `prev.next = x`

時間：O(1)

### 5.4 刪除某節點後面那個（Delete After prev）

1. `target = prev.next`
2. `prev.next = target.next`
3. free/delete `target`

時間：O(1)

---

## 6. Head / Tail 指標與 Dummy Node（哨兵節點）

### 6.1 Tail 指標

如果維護 `tail`：

* 尾插可變成 O(1)
* 需小心更新 tail（尤其刪除最後一個節點）

### 6.2 Dummy Node（Sentinel / 哨兵）

常見技巧：使用一個固定的 dummy node 讓 head 插入/刪除更一致。

例：刪除符合條件的節點時：

* `dummy.next = head`
* 用 `prev = dummy` 走訪
* 避免「刪 head」需要特判

---

## 7. 常見 bug 與邊界情況（高頻考點）

### 7.1 空串列（head = null）

* 插入通常沒問題
* 刪除/讀取必須先檢查

### 7.2 單一節點

* 刪除 head 後 head 變 null
* 若有 tail，tail 也必須同步變 null

### 7.3 指標順序錯誤

插入時若先改 `prev.next`，可能丟失原本鏈結。
正確習慣：**先接好新節點的 next，再把前節點指向新節點**。

### 7.4 記憶體管理（C/C++）

* 刪除節點後記得 free/delete
* 避免 use-after-free（釋放後繼續用指標）
* 避免 memory leak（配置後沒有釋放）

---

## 8. Linked List 的典型演算法

### 8.1 快慢指標（Fast & Slow Pointers）

用途：

* 找中間節點
* 偵測 cycle（Floyd cycle detection）
* 找 cycle 入口

**偵測環（Cycle detection）概念**

* `slow` 一次走 1 步
* `fast` 一次走 2 步
* 若有環，fast 會追上 slow；無環則 fast 會到 null

時間：O(n)，空間：O(1)

---

### 8.2 反轉鏈結串列（Reverse Linked List）

核心三指標：

* `prev`
* `cur`
* `next`

流程（概念）：

1. 保存 `next = cur.next`
2. `cur.next = prev`（反向）
3. `prev = cur`
4. `cur = next`

時間：O(n)，空間：O(1)

---

### 8.3 合併兩個排序鏈結串列（Merge Two Sorted Lists）

* 使用 dummy node
* 逐步比較兩條 list 的 head，接到結果尾端

時間：O(n+m)

---

### 8.4 刪除倒數第 k 個節點（Two pointers）

* `fast` 先走 k 步
* 然後 `fast` 和 `slow` 一起走
* fast 到尾時，slow 在倒數第 k 的前一個（便於刪除）

---

## 9. Linked List vs Array

| 面向            | Array        | Linked List   |
| ------------- | ------------ | ------------- |
| 記憶體配置         | 連續           | 分散            |
| Random Access | **O(1)**     | **O(n)**      |
| 插入/刪除（已定位）    | O(n)（需搬移）    | **O(1)**（改指標） |
| 搜尋            | O(n)（未排序）    | O(n)          |
| Cache 友善度     | 好            | 較差            |
| 擴容            | 動態陣列需 resize | 天生動態          |

總結：

* **需要大量 index 存取**：偏向 array
* **需要頻繁插入刪除且位置已知/靠近頭部**：偏向 linked list

---

## 10. 常用模板

### Dummy node 刪除模板（概念）

* `dummy.next = head`
* `prev = dummy, cur = head`
* 走訪：

  * 若要刪 cur：`prev.next = cur.next`，cur 後移
  * 否則：prev、cur 一起後移
* 回傳 `dummy.next`

---
