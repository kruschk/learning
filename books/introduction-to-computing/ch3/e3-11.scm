; e3-11
; method 1
(define bigger
  (lambda (a b)
    (if (> a b) #t #f)))

(define biggest1
  (lambda (a b c)
    (if (bigger a b)
      (if (bigger a c) a c)
      (if (bigger b c) b c))))

(biggest1 0 212 -46)

; method 2
(define biggest2
  (lambda (a b c)
    (if (> a b)
      (if (> a c) a c)
      (if (> b c) b c))))

(biggest2 1 2 -3)
