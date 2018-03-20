(define (fib n) (fibhelp n 1 1))
(define (fibhelp n a b)
  (if (= n 0) a
    (fibhelp (- n 1) b (+ a b))
  )
)
