(define (filt P L) (if (null? L) L
                     (if (P (car L)) 
                       (cons (car L) (filt P (cdr L)))
                       (filt P (cdr L)))))
