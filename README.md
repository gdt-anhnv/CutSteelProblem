# CutSteelProblem
Bài toán chia thép:
yêu cầu cắt được các thanh thép có độ dài khác nhau (l1, l2, l3, ...)
từ thanh thép có độ dài tối đa ban đầu là L (L > l_i, i =1,n).
Tính số lượng cây thép độ dài L tối thiểu cần thiết để cắt được đủ số lượng thép yêu cầu.

# Phân tích bài toán
Ở đây chúng ta có 2 bài toán cần giải quyết:
  1. Các cách cắt thép từ cây thép L. Ví dụ: (c1) l1 + l2, (c2) 2*l2 + l3 + l4, ....
  2. Bài toán tối ưu min c1 + c2 + ... + cn thỏa mãn về số lượng thép cho từng loại

# Giải pháp
