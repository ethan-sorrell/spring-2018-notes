(define (flatten L) (if (pair? L) 
                      (append (flatten (car L)) (flatten (cdr L)))
                      (if (null? L) L
                        (cons L '()))))
