(define (m f L) (if (null? L) L
  (cons (f (car L)) (m f (cdr L)))))

