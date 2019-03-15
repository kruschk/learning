; e3-10
(define (absvalue x) (if (< x 0) (- x) x))
(define (bigger-magnitude x y) (if (> (absvalue x) (absvalue y)) x y))
(bigger-magnitude -15 99)
