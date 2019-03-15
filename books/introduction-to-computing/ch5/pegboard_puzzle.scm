#!/usr/bin/racket
#lang racket

; data abstraction example (pegboard puzzle)

; Position

; list-get-element procedure from 5.3
(define (list-get-element p n)
  (if (null? p)
    (error "index out of range")
    (if (= n 1) (car p) (list-get-element (cdr p) (- n 1)))))

; tlist datatype
(define (make-tlist tag p) (cons tag p))
(define (tlist-get-tag p) (car p))

(define (tlist-get-element tag p n)
  (if (eq? (tlist-get-tag p) tag)
    (list-get-element (cdr p) n)
    (error (format "Bad tag: ~a (expected ~a)"
                   (tlist-get-tag p) tag))))

; Position datatype
(define (make-position row col) (make-tlist 'Position (list row col)))
(define (position-get-row posn) (tlist-get-element 'Position posn 1))
(define (position-get-column posn) (tlist-get-element 'Position posn 2))

; Move

; Direction datatype
(define (make-direction right down)
  (make-tlist 'Direction (list right down)))
(define (direction-get-horizontal dir) (tlist-get-element 'Direction dir 1))
(define (direction-get-vertical dir) (tlist-get-element 'Direction dir 2))

; Move datatype
(define (make-move start direction)
  (make-tlist 'Move (list start direction)))
(define (move-get-start move) (tlist-get-element 'Move move 1))
(define (move-get-direction move) (tlist-get-element 'Move move 2))

(define (direction-step pos dir)
  (make-position
    (+ (position-get-row pos) (direction-get-vertical dir))
    (+ (position-get-column pos) (direction-get-horizontal dir))))

(define (move-get-jumped move)
  (direction-step (move-get-start move) (move-get-direction move)))
(define (move-get-landing move)
  (direction-step (move-get-jumped move) (move-get-direction move)))

; Board

(define (make-list-of-constants n val)
  (if (= n 0) null (cons val (make-list-of-constants (- n 1) val))))

; list-append
(define (list-append p q)
  (if (null? p)
    q
    (cons (car p) (list-append (cdr p) q))))

(define (make-board rows)
  (if (= rows 0) null
    (list-append (make-board (- rows 1))
                 (list (make-list-of-constants rows #t)))))

(define (board-rows board) (length board))

(define (board-valid-position? board pos)
  (and (>= (position-get-row pos) 1) (>= (position-get-column pos) 1)
       (<= (position-get-row pos) (board-rows board))
       (<= (position-get-column pos) (position-get-row pos))))

; list-sum
(define (list-sum p)
  (if (null? p) 0 (+ (car p) (list-sum (cdr p)))))

; list-map
(define (list-map f p)
  (if (null? p) null
    (cons (f (car p))
          (list-map f (cdr p)))))

; list-flatten
(define (list-flatten p)
  (if (null? p) null
    (list-append (car p) (list-flatten (cdr p)))))

(define (board-number-of-pegs board)
  (list-sum
    (list-map (lambda (peg) (if peg 1 0)) (list-flatten board))))

(define (board-is-winning? board)
  (= (board-number-of-pegs board) 1))

(define (board-contains-peg? board pos)
  (list-get-element (list-get-element board (position-get-row pos))
                    (position-get-column pos)))

(define (row-replace-peg pegs col val)
  (if (= col 1)
    (cons val (cdr pegs))
    (cons (car pegs) (row-replace-peg (cdr pegs) (- col 1) val))))

(define (board-replace-peg board row col val)
  (if (= row 1)
    (cons (row-replace-peg (car board) col val) (cdr board))
    (cons (car board) (board-replace-peg (cdr board) (- row 1) col val))))

(define (board-add-peg board pos)
  (if (board-contains-peg? board pos)
    (error (format "Board already contains peg at position ~a" pos))
    (board-replace-peg board (position-get-row pos)
                       (position-get-column pos) #t)))

(define (board-remove-peg board pos)
  (if (not (board-contains-peg? board pos))
    (error (format "Board does not contain peg at position ~a" pos))
    (board-replace-peg board (position-get-row pos)
                       (position-get-column pos) #f)))

(define (board-execute-move board move)
  (board-add-peg
    (board-remove-peg
      (board-remove-peg board (move-get-start move))
      (move-get-jumped move))
    (move-get-landing move)))

; Finding valid moves

; intsto
(define (intsto n)
  (if (= n 0)
    null
    (list-append (intsto (- n 1))
      (list n))))

(define (all-positions-helper board)
  (list-map
    (lambda (row) (list-map (lambda (col) (make-position row col))
                            (intsto row)))
    (intsto (board-rows board))))

(define (all-positions board)
  (list-flatten (all-positions-helper board)))

(define all-directions
  (list
    (make-direction -1  0) (make-direction 1  0)   ; left, right
    (make-direction -1 -1) (make-direction 0 -1)   ; up-left, up-right
    (make-direction  0  1) (make-direction 1  1))) ; down-left, down-right

(define (all-conceivable-moves board)
  (list-flatten
    (list-map
      (lambda (pos) (list-map (lambda (dir) (make-move pos dir))
                              all-directions))
      (all-positions board))))

; list-filter
(define (list-filter test p)
  (if (null? p) null
    (if (test (car p))
      (cons (car p) (list-filter test (cdr p)))
      (list-filter test (cdr p)))))

(define (all-board-moves board)
  (list-filter
    (lambda (move) (board-valid-position? board (move-get-landing move)))
    (all-conceivable-moves board)))

(define (all-legal-moves board)
  (list-filter
    (lambda (move)
      (and
        (board-contains-peg? board (move-get-start move))
        (board-contains-peg? board (move-get-jumped move))
        (not (board-contains-peg? board (move-get-landing move)))))
    (all-board-moves board)))

; Winning the game

(define (solve-pegboard board)
  (if (board-is-winning? board)
    null ; no moves needed to reach winning position
    (try-moves board (all-legal-moves board))))

(define (try-moves board moves)
  (if (null? moves)
    #f ; didn't find a winner
    (if (solve-pegboard (board-execute-move board (car moves)))
      (cons (car moves)
            (solve-pegboard (board-execute-move board (car moves))))
      (try-moves board (cdr moves)))))

(time (solve-pegboard (board-remove-peg (make-board 5) (make-position 1 1))))
