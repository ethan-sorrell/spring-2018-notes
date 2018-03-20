(define T1 '(a (b (e) (f (k))) (c (g)) (d (h (m) (n) (p)) (j))))

(define (postorder T) (append (fold-left append '() (map postorder (cdr T))) (list (car T))))
