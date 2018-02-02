(define (rev L) (help L '()))
(define (help L1 L2) (if (null? L1) L2
                       (help (cdr L1) (cons (car L1) L2))))
