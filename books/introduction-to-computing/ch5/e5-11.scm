; e5-11
(define (list-test p)
  (if (null? p)
    #t
    (if (number? (car p))
      (if (list-test (cdr p))
        #t
        #f)
      #f)))

(list-test (list 1 2 3 4 5))
