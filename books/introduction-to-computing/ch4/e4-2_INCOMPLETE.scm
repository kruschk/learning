; e4-2
1. (((fcompose self-compose self-compose) inc) 1)
2. ((((lambda (f g) (lambda (x) (g (f x)))) self-compose self-compose) inc) 1)
3. (((lambda (x) (self-compose (self-compose x))) inc) 1)
4. ((self-compose (self compose inc)) 1)
5. ((self-compose ((lambda (f) (fcompose f f)) inc)) 1)
6. ((self-compose (fcompose inc inc)) 1)
