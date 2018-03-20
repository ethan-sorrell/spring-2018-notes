(define (practice_log m q) (if (= q 1) 0
                      (+ (practice_log m (/ q m)) 1)))
