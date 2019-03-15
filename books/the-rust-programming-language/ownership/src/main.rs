fn main() {
    let s1 = String::from("hello");
    let (s2, len) = calculate_length(s1);
    println!("The length of \"{}\" is {}.", s2, len);
}

fn calculate_length(a_string: String) -> (String, usize) {
    let length = a_string.len();
    (a_string, length)
}
