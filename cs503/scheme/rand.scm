(define (mk-random) ; this is our class
  (let ((seed 19380110) (n 4294967296))
    (lambda (m) (set! seed (modulo (+ (* seed 69069) 1) n))
      (modulo seed m))))
(define rand (mk-random)) ; this is an instance of our class
