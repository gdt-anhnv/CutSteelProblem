# CutSteelProblem
Bài toán chia thép:
yêu cầu cắt được các thanh thép có độ dài khác nhau (l1, l2, l3, ...)
từ thanh thép có độ dài tối đa ban đầu là L (L > l_i, i =1,n).
Tính số lượng cây thép độ dài L tối thiểu cần thiết để cắt được đủ số lượng thép yêu cầu.

VD:
Cần:
  1. 100 cây thép 2m
  2. 200 cây thép 3m
  3. 50 cây thép 5m
  4. 117 cây thép 7m
Tính số cây thép 10m tối thiểu để đáp ứng đủ số thép yêu cầu.

# Phân tích bài toán
Ở đây chúng ta có 2 bài toán cần giải quyết:
  1. Các cách cắt thép từ cây thép L. Ví dụ: (a1) l1 + l2, (a2) 2*l2 + l3 + l4, ....
  2. Bài toán tối ưu min a1 + a2 + ... + an thỏa mãn về số lượng thép cho từng loại

# Giải pháp
A. Vấn đề các cách cắt thép
Như ví dụ ở trên, ta cần cắt thanh thép 10m thành các thành nhỏ hơn là 2m, 3m, 5m và 7m.
Có nhiều cách cắt thỏa mãn:
  1. 7m + 3m
  2. 5m + 3m + 2m
  3. 3m + 3m + 2m + 2m + 2m
  4. 7m + 2m
  5. 5m + 2m + 2m
  ...
Như vậy, không chỉ phải tìm các cách cắt vừa đủ 10m, ta còn phải xét cả các cách cắt không đủ 10m.
Bài toán liệt kê này có thể được xử lý một cấu trúc dữ liệu dạng cây như sau:
  1. Node có 2 giá trị, A và B
            A: giá trị độ dài thanh thép (7m, 5m, 3m, 2m)
            B: B_child = B_parent - A_child (parent là node cha, child là node con)
  2. Giá trị B >= 0
  3. Một node có thể có nhiều node con
Một cách cắt thép sẽ là một list các giá trị A đi từ root đến leaf.
Với cách sử dụng cây như vậy, một cách cắt sẽ bị lặp lại nhiều lần. Vì vậy, sau khi duyệt lấy tất cả
các cách cắt thì cần loại bỏ những cách bị trùng nhau.

B. Bài toán tối ưu số lượng thanh
Giả sử đã tìm được các cách chia thép như trên, ta có một phát biểu:
  1. a1 * (7m + 3m)
  2. a2 * (5m + 3m + 2m)
  3. a3 * (3m + 3m + 2m + 2m + 2m)
  4. a4 * (7m + 2m)
  5. a5 * (5m + 2m + 2m)
  ....
  
Min (a1 + a2 + a3 + a4 + a5 + ... + an) thỏa mãn
  1. a1 + a4 + .. = 117
  2. a2 + a5 + .. = 50
  3. a1 + a2 + 2 * a3 + .. = 200
  4. a2 + 3 * a3 + a4 + 2 *a5 + .. = 100
  ...
  
Bài toàn ta có thể dễ dàng giải được bằng phương pháp đơn hình Big M (Simplex Method - Big M)
