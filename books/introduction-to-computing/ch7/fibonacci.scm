#!/usr/bin/racket
#lang racket

(define (fibo n)
  (if (or (= n 1) (= n 2)) 1
	(+ (fibo (- n 1)) (fibo (- n 2)))))

(time (fibo 10))
(time (fibo 30))
(time (fibo 40))
