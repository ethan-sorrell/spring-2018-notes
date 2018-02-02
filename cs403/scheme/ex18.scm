(define L ((lambda (x) (* x x x)) (lambda (x) (* 2 x)) (lambda (x) (* x x))))
(define (invmap ListFuncts x) (if (null? ListFuncts) ListFuncts
                                (cons ((car ListFuncts) x) (invmap (cdr ListFuncts) x))))
