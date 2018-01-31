(define L '(1 4 a b 9 d e f))
(define (reject P L) (if (null? L) L
                       (if (P (car L)) (reject P (cdr L))
                         (cons (car L) (reject P (cdr L))))))
