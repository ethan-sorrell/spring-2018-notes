(define f (lambda (x) (+ x x)))

(define g (lambda (x) (* x x x)))

(let ((f (lambda (x) (- x 5))) (g (lambda (x) (f (+ x 1))))) (g 10)) 
; this works fine
; we may use global 

; but this will not work as intented
(let* ((g (lambda (x) (if (<= x 0) 0 (+ 2 (g (- x 3))))))) (g 10))

; however this will
(letrec ((g (lambda (x) (if (<= x 0) 0 (+ 2 (g (- x 3))))))) (g 10))

; if List redefines functions that should be called recursively, letrec should be used
; essentially when we want to use our local version of a function, within that functions definition, we should use letrec
