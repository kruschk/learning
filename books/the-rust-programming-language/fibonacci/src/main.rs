use std::io;

fn main() {
    println!("Please enter the index of the desired fibonacci number.");
    loop {
        // get number from stdin, as String
        let mut n = String::new();
        io::stdin().read_line(&mut n)
            .expect("Failed to read line.");
        // convert to uint
        let mut n: u8 = match n.trim().parse() {
            Ok(n) => n,
            Err(_) => continue
        };
        // calculate fibonacci(n)
        let fib: u128 = match n {
            0 => 0,
            _ => {
                let mut prev_prev = 0;
                let mut prev = 1;
                let mut ans = 1;
                while n > 1 {
                    n -= 1;
                    ans = prev_prev + prev;
                    prev_prev = prev;
                    prev = ans;
                }
                ans
            }
        };
        // print result
        println!("{}", fib);
        break;
    }
}
