extern crate rand;

use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    // introduce the player to the game and generate a random number
    println!("Guess the number!");
    let secret_number = rand::thread_rng().gen_range(1, 101);
    // allow the player to guess until they guess the correct value
    loop {
        // get the guess from stdin as a string, convert it to u8, and echo
        println!("Please input your guess.");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("Failed to read line");
        let guess: u8 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        println!("You guessed: {}", guess);
        // match the guess with the secret number and break if it is correct
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            },
        };
    }
}
