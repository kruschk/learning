; e3-8
(define (xor bool1 bool2) (if bool1 (if bool2 #f #t) (if bool2 #t #f)))
(xor #f #t)
