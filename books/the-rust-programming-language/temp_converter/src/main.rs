use std::io;

fn main() {
    println!("Please enter a temperature, in degrees Fahrenheit.");
    loop {
        let mut deg_f = String::new();
        io::stdin().read_line(&mut deg_f).expect("Failed to read line");
        let deg_f: f32 = match deg_f.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please enter a number");
                continue;
            },
        };
        println!("{}", 5.0*(deg_f - 32.0)/9.0);
        break;
    };
}
