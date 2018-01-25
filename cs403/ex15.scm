(define L1 '(2 4 5 7 8 10))

(map (lambda (x) (* x x x)) L1)

(fold-left (lambda (m n) (cons n m)) '() L1)
