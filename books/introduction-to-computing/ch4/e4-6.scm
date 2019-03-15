; e4-6
(define gauss-sum
  (lambda (n)
    (if (= n 1)
      n
      (+ n (gauss-sum (- n 1))))))

(gauss-sum 100)
