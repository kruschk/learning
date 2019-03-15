; e5-17
(define (list-increment p)
  (if (null? p)
    ()
    (cons (+ 1 (car p)) (list-increment (cdr p)))))

(list-increment (list 1 2 3 4))
