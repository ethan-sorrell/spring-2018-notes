(define L '(18 4 2 3 1 10 33 8 9))

(define (selection-sort L) (selection-helper L '()))

(define (selection-helper Unsorted Sorted) (if (null? Unsorted) Sorted
                                             (selection-helper (rem (minEle Unsorted) Unsorted) (cons (minEle Unsorted) Sorted))))

(define (rem I L) (if (null? L) L
                      (if (= (car L) I) (cdr L)
                          (cons (car L) (rem I (cdr L))))))

(define (minEle L) (fold-left (lambda (x y) (if (> x y) x y)) (car L) (cdr L)))

