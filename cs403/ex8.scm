(define (e L1 L2) (if (and (pair? L1) (pair? L2)) 
                      (and (e (car L1) (car L2)) (e (cdr L1) (cdr L2)))
                      (eq? L1 L2)))
