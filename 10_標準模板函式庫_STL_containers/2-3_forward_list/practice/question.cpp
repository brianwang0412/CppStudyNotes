/*
================================================================================
【forward_list 綜合練習題】

目的: 測試是否完全熟悉 std::forward_list 的宣告、新增、存取、刪除、
      遍歷與各項成員函式(尤其是與list/vector「命名不同」或「行為不同」的部分)

請在下方 main() 中，依照題目描述「依序」完成以下操作，並將每一小題要求印出的
結果依序輸出(元素之間以一個空白分隔，最後換行；每小題印出前請先印出題號分隔線，
例如 cout<<"(1) "; 方便對照)。完成後可與後面的參考解答比對。

--------------------------------------------------------------------------------
(1) 宣告一個空的 forward_list<int> fl。
    用 push_front() 依序加入 5, 4, 3, 2, 1 (加入後 fl 應變成 {1,2,3,4,5})，
    印出 fl。

(2) 用 insert_after() 在「值為3」的節點之後插入 999，印出 fl。
    (此時 fl 應為 {1,2,3,999,4,5})

(3) 用 before_begin() 搭配 insert_after()，在 fl 的「最開頭」插入 0，印出 fl。
    (此時 fl 應為 {0,1,2,3,999,4,5})

(4) 用 erase_after(before_begin()) 刪除 fl 的第一個元素(0)，印出 fl。
    (此時 fl 應為 {1,2,3,999,4,5})

(5) 用 remove() 刪除 fl 中所有值為 999 的元素，印出 fl。
    (此時 fl 應為 {1,2,3,4,5})

(6) forward_list 沒有 size()，請用 std::distance() 計算並印出 fl 目前的長度。

(7) 建立 forward_list<int> fl2 = {100, 200, 300}。
    請自行找到 fl 的「最後一個元素」的 iterator(forward_list 沒有 back() 迭代器，
    須自己從 begin() 走訪到底)，用 splice_after() 把 fl2 的「全部」節點搬移到
    fl 的最後一個元素之後。印出搬移後的 fl 與 fl2。
    (此時 fl 應為 {1,2,3,4,5,100,200,300}，fl2 應為空)

(8) 用 emplace_front() 在 fl 開頭加入 0，
    再用 emplace_after() 在 fl 的「第一個元素之後」插入 -1，印出 fl。
    (此時 fl 應為 {0,-1,1,2,3,4,5,100,200,300})

(9) 用 fl.sort(greater<int>()) 將 fl 由大到小排序，印出 fl。

(10) 用 fl.reverse() 將 fl 反轉(使其變回由小到大)，印出 fl。

(11) 用 remove_if() 搭配 Lambda，刪除 fl 中所有「大於等於100」的元素，印出 fl。
    (此時 fl 應為 {-1,0,1,2,3,4,5})

(12) 用 <algorithm> 的 find() 尋找 fl 中值為 3 的節點，
    若找到，印出 "Found at index X"(X 用 std::distance() 計算)；
    若找不到，印出 "Not Found"。

(13) 用 <algorithm> 的 count() 計算 fl 中「值為奇數」的元素個數並印出。
    (提示: count_if() 搭配 Lambda 判斷奇偶)

(14) 用 <numeric> 的 accumulate() 計算 fl 目前所有元素的總和，印出。

(15) 建立 forward_list<int> flA = {1,4,7}, flB = {2,5,8}(皆已排序)，
    用 merge() 將 flB 合併進 flA，印出 flA 與 flB。

(16) 建立 forward_list<int> flC = {1,2,3,4,5}, flD = {10,20,30,40,50}。
    用 splice_after(pos, other, it) 這個版本，把 flD 中「begin()之後」的那個節點
    (也就是20)搬移到 flC 的 begin() 之後，印出 flC 與 flD。
    (此時 flC 應為 {1,20,2,3,4,5}，flD 應為 {10,30,40,50})
    注意: forward_list::splice_after(pos,other,it) 搬移的是「it之後」的節點，
          與 list::splice(pos,other,it) 搬移「it本身」的語意不同!

(17) 建立 forward_list<forward_list<int>> ff，用 push_front() 依序放入資料，
    使其最終內容為 {{1,2,3}, {4,5,6}}(注意 push_front 放入順序需相反)。
    用巢狀迴圈印出 ff 的每一列(一列一行)。

(18) 承(17)，用 ff.front().push_front(0) 在第一列開頭加入0，
    再印出 ff 的每一列，驗證只有第一列被修改。
================================================================================
*/