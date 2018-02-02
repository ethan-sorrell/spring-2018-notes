(define L '(1 2 (a b) (3 (4 c) d) ((e f) (5 6)) g 7))

(define (twist L)
       (if (not (pair? L)) L
         (reverse (map twist L))))
