; e4-13
(define factorial-helper
  (lambda (n result)
    (if (= n 1)
      result
      (factorial-helper (- n 1) (* n result)))))

(define factorial
  (lambda (n)
    (factorial-helper n 1)))

(factorial 0)
