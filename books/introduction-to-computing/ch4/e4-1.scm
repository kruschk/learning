; e4-1
(define square
  (lambda (x)
    (* x x)))

(define cube
  (lambda (x)
    (* x x x)))

(define sixth-power
  (lambda (x)
    (cube (square x))))

(define fog
  (lambda (f g x)
    (g (f x))))

(fog square cube 3)

(define inc (lambda (x) (+ x 1)))

(define fcompose
  (lambda (f g)
    (lambda (x) (g (f x)))))

((fcompose square square) 3)                                ; a. result will be (x^2)^2, or 81
(fcompose (lambda (x) (* x 2)) (lambda (x) (/ x 2)))        ; b. result is #<Closure>, i.e a procedure
((fcompose (lambda (x) (* x 2)) (lambda (x) (/ x 2))) 1120) ; c. result is x for any input (so 1120)
((fcompose (fcompose inc inc) inc) 2)                       ; d. result is 5
