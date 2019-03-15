#!/usr/bin/racket
#lang racket

(define (fast-fibo n)
  (define (fibo-iter a b left)
	(if (<= left 0)
	  b
	  (fibo-iter b (+ a b) (- left 1))))
  (fibo-iter 1 1 (- n 2)))

(time (fast-fibo 10))
(time (fast-fibo 30))
(time (fast-fibo 60))
