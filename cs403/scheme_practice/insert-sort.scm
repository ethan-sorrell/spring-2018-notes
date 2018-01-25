(define (insertion-sort L) (repeat (- (length L) 1) L))

(define (repeat k L) (if (= k 0) L
                       (repeat (- 1 k) (insertion-helper L))))

(define (insertion-helper L) (if (or? (null? L) (null? (cdr L))) L
                               (
