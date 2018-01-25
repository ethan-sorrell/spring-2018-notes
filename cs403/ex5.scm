(define (bubble-up L) (if (or (null? L) (null? (cdr L))) L 
                        (if (< (car L) (cadr L)) 
                          (cons (car L) (bubble-up (cdr L)))
                          (cons (cadr L) (bubble-up (cons (car L) (cddr L))))
                          )))
(define (repeat k L)
  (if (= k 0) L
    (repeat (- k 1) (bubble-up L))))

(define (bubble-sort L) (repeat (- (length L) 1) L))


