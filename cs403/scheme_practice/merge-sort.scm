(define L '(11 18 9 27 3 25 21 2 3 9))

(define (merge-sort L) (if (or (null? L) (null? (cdr L))) L
  (merge (merge-sort (even L)) (merge-sort (even (cdr L))))))

(define (merge L1 L2) (if (null? L1) L2
                        (if (null? L2) L1
                          (if (< (car L1) (car L2))
                            (cons (car L1) (merge (cdr L1) L2))
                            (cons (car L2) (merge L1 (cdr L2)))))))

(define (even L) (if (or (null? L) (null? (cdr L))) L
                   (cons (car L) (even (cddr L)))))
