(define (z L1 L2) (if (or (null? L1) (null? L2)) '()
                    (cons (list (car L1) (car L2)) (z (cdr L1) (cdr L2)))))

(define (zw op L1 L2) (if (or (null? L1) (null? L2)) '()
                        (cons (op (car L1) (car L2)) (zw op (cdr L1) (cdr L2)))))

