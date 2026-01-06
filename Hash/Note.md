# Hash（雜湊）筆記

## 1. 定義與核心概念

**Hash（雜湊）**是一種把「鍵（key）」映射到「索引/位置（index）」的技術，用於快速查找、插入、刪除資料。
典型資料結構是 **Hash Table（雜湊表）**，其核心流程為：

1. 對 key 套用 **hash function（雜湊函數）** 得到 hash code（雜湊值）
2. 將 hash code 轉成表格索引（bucket index）
3. 在對應 bucket 中存取資料

目標：讓查找/插入/刪除在平均情況下接近 **O(1)**。

---

## 2. Hash Function（雜湊函數）

### 2.1 雜湊函數的目的

雜湊函數將 key 映射到整數空間，理想目標：

* **分佈均勻**：避免大量 key 落在同一 bucket（降低碰撞）
* **效率高**：計算成本低
* **確定性**：同一 key 必須得到同一 hash code
* **抗結構性輸入**：對規律輸入不應產生嚴重聚集

### 2.2 索引計算（bucket index）

常見方式：

* `index = hash(key) mod m`

其中 `m` 是 table size（bucket 數量）。

---

## 3. Hash Collision（雜湊碰撞）

**Collision（碰撞）**：兩個不同 key 映射到相同 bucket index。
碰撞是不可避免的（有限 bucket 對無限/大量 key），因此必須有 **collision resolution（碰撞處理）**。

---

## 4. Collision Resolution（碰撞處理策略）

主要分兩大類：**Separate Chaining** 與 **Open Addressing**。

---

### 4.1 Separate Chaining（分離鏈結法）

每個 bucket 存一個「容器」（常見是 linked list，也可用 dynamic array / balanced tree）。

結構示意：

```
bucket[0] -> (k1,v1) -> (k2,v2) -> ...
bucket[1] -> (k3,v3) -> ...
...
```

操作：

* 插入：計算 index，加入 bucket 的容器
* 查找：計算 index，在 bucket 內線性/樹狀查找
* 刪除：計算 index，在 bucket 內移除節點

複雜度（令 α = load factor）：

* 平均：O(1 + α)
* 最差：O(n)（全部落同 bucket）

特性：

* 優點：實作直觀、刪除容易、對高 load factor 較不敏感
* 缺點：額外指標/容器開銷、cache locality 較差

---

### 4.2 Open Addressing（開放定址法）

bucket 本身直接存放元素；若發生碰撞，就依「探測序列（probe sequence）」找下一個可用位置。

重要限制：

* 同一時間 table 內必須有空槽
* 刪除需要特殊處理（tombstone）

常見探測方法：

#### 4.2.1 Linear Probing（線性探測）

```
index, index+1, index+2, ... (mod m)
```

特性：

* 優點：簡單、cache friendly
* 缺點：容易形成 **primary clustering（主聚集）**

#### 4.2.2 Quadratic Probing（二次探測）

```
index + 1^2, index + 2^2, index + 3^2, ... (mod m)
```

特性：

* 改善主聚集，但仍可能有 **secondary clustering（次聚集）**
* 需要適當的 m 與探測設計以保證能探測到空槽

#### 4.2.3 Double Hashing（雙重雜湊）

使用第二個雜湊函數決定步長：

```
index_i = (h1(key) + i * h2(key)) mod m
```

特性：

* 通常能有效降低聚集問題
* 需確保 `h2(key)` 不為 0，且步長與 m 的關係能遍歷表格（常見要求 gcd(step, m)=1）

---

## 5. Load Factor（負載因子）

**Load Factor（α）**衡量 table 的擁擠程度：

* **Chaining**：`α = n / m`（n:元素數量；m:bucket 數）
* **Open addressing**：同樣用 `α = n / m`，但 α 必須 < 1

影響：

* α 越大，碰撞越多，操作平均成本上升
* 設計上通常會設定一個閾值（例如 0.7~0.9），超過就進行 rehash

---

## 6. Rehash / Resize（重雜湊 / 擴容）

當 table 過於擁擠，需要：

1. 建立更大的 table（m' > m）
2. 重新將所有元素依新的 m' 放入（重新計算 index）
3. 更新 table 參考

重點：

* rehash 成本是 O(n)，但若擴容策略合理，平均攤提成本可維持接近 O(1)

---

## 7. Deletion（刪除）語意差異

### 7.1 Chaining 的刪除

* 在 bucket 容器中直接移除對應節點即可
* 不影響其他 bucket 的可達性

### 7.2 Open Addressing 的刪除（Tombstone）

若直接清空 slot，可能破壞後續探測的查找路徑（查找會提早停止）。

因此常用 **tombstone（刪除標記）**：

* slot 標記為「已刪除」但不是「從未使用」
* 查找時仍要繼續探測
* 插入時可重用 tombstone slot
* tombstone 累積過多會使效能下降，常搭配 rehash 清理

---

## 8. Hash Table 的操作複雜度總結

| 操作     | 平均情況 | 最差情況 |
| ------ | ---: | ---: |
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |

最差情況通常來自：

* 極端碰撞（大量 key 落同 bucket）
* 不良 hash function
* 過高 load factor
* open addressing 探測序列導致長探測鏈

---

## 9. Hash 的常見應用（資料結構/系統層面）

### 9.1 Set / Map

* **Hash Set**：只存 key（判斷是否存在）
* **Hash Map / Dictionary**：存 key → value

### 9.2 快速去重與統計

* 去重：把元素當 key 放入 set
* 計數：key 為元素，value 為出現次數（frequency table）

### 9.3 快取與索引

* 快取表（cache table）用 key 快速定位資料
* 記憶體中的索引結構（例如 symbol table）

---

## 10. 設計要點與不變量（Invariant）

### 10.1 Chaining

* 每個 bucket 容器只存放 hash 到該 index 的元素
* 查找必須先算 index 再在該 bucket 內比對 key（避免只看 hash code）

### 10.2 Open Addressing

* 探測序列必須一致（insert/search/delete 用同一探測規則）
* slot 狀態需區分至少三種：

  * EMPTY（從未使用）
  * OCCUPIED（已使用）
  * DELETED（tombstone）

---

## 11. 常見名詞對照

* **Key**：用來索引/查找的識別值
* **Value**：與 key 對應的資料
* **Hash function**：將 key 映射到整數的函數
* **Bucket**：雜湊表的一格（槽），或指該格對應的容器
* **Collision**：不同 key 落到同一 bucket
* **Chaining**：bucket 內用容器存多筆資料
* **Open addressing**：碰撞後改用探測序列找其他空槽
* **Load factor（α）**：n/m，衡量擁擠程度
* **Rehash**：換更大表並重新插入所有元素
* **Tombstone**：開放定址法刪除時的「已刪除」標記

---
