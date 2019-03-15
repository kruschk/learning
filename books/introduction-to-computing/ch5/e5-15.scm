; e5-15
(define (list-last-element p)
  (if (null? p)
    (error "list is empty")
    (recurse p)))

(define (recurse p)
  (if (null? (cdr p))
    (car p)
    (list-last-element (cdr p))))

(list-last-element ())
