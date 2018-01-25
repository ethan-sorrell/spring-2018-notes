(define f (lambda (x) (+ x x)))

(define g (lambda (x) (* x x x)))

(let ((f (lambda (x) (- x 5))) (g (lambda (x) (f (+ x 1))))) (g 10)) ; this works fine

; but this will not work
(let* ((f (lambda (x) (- x 5))) (g (lambda (x) ((if (<= x 0) 0 (+ 2 (g (- x 3)))))))) (g 10))
