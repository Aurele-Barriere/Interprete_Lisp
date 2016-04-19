(setq f (lambda (n) (+ 1 n)))
(setq fact (lambda (n) (if (= n 0) 1 (* n (fact (- n 1))))))
(setq fibo (lambda (n) (if (= n 0) 1 (if (= n 1) 1 (+ (fibo (- n 1)) (fibo (- n 2)))))))
