; e4-5
(define factorial
  (lambda (n)
    (if (= n 0)
      1
      (* n (factorial (- n 1))))))

; a (this procedure is NCK(N,K) = N!/((N-K)!*K!))
(define choose
  (lambda (n k)
    (/ (factorial n) (* (factorial (- n k)) (factorial k)))))
; b (number of ways to choose 5 cards in a deck of 52)
(choose 52 5) ; = 2,598,960
; c (likelihood of selecting a flush, defined as 5 cards of the same suit)
(/ (* 4 (choose 13 5)) (choose 52 5)) ; ~= 0.00198
