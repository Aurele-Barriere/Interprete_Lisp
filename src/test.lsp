(setq f (lambda (n) (+ 1 n)))
(setq fact (lambda (n) (if (= n 0) 1 (* n (fact (- n 1))))))
(+ 3 5)
