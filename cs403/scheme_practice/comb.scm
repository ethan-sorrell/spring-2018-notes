    (define (comb n k) (if (= k 1) n
                         (* (comb (- n 1) (- k 1)) (/ n k))))
