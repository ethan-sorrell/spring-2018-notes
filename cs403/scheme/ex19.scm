(define (raiseto n) (lambda (m) (expt m n)))

(define fourth-power (raiseto 4))
