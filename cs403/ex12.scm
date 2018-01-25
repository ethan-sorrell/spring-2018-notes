(define (foldl op id L) (if (null? L) id
                          (foldl op (op id (car L)) (cdr L))))

(define (foldr op id L) (if (null? L) id 
                          (op (car L) (foldr op id (cdr L)))))

(define (swapcons x y) (cons y x))
