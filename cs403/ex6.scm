(define (app L1 L2) (if (null? L1) L2 
                      (cons (car L1) (app (cdr L1) L2))))
