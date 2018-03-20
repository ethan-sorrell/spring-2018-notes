(define L '(1 38 28 9 8 6 1 23 3))
(define (insertion-sort L) (insertion-helper '() L))

(define (insert I L) (if (null? L) (cons I L)
                       (if (< (car L) I)
                         (cons (car L) (insert I (cdr L)))
                         (cons I L))))
                      ; cons all items less than I
                      ; cons I
                      ; cons all items greater than I

(define (insertion-helper Sorted Unsorted) (if (null? Unsorted) Sorted
                                               (insertion-helper (insert (car Unsorted) Sorted) (cdr Unsorted))))
