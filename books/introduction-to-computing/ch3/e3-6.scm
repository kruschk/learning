; e3-6
(define (compute-cost price tax-rate) (* price (+ 1 tax-rate)))
(compute-cost 13 0.05)

(define (compute-cost% price tax-rate%) (* price (+ 1 (/ tax-rate% 100))))
(compute-cost% 13 5)
