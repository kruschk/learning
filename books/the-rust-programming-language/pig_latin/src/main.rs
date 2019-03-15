
fn to_pig_latin(word: &str) -> String {
    const VOWELS: &str = "aeiou";
    let letters: Vec<char> = word.chars().collect();
    let first_char = letters[0];
    let mut second_onward: String = letters[1..].into_iter().collect();
    second_onward.push('-');
    if VOWELS.contains(first_char) {
        second_onward.push_str("hay");
    } else {
        second_onward.push(first_char);
        second_onward.push_str("ay");
    }
    second_onward
}

fn pig_latinize(text: &str) -> String {
    let mut output: Vec<String> = Vec::new();
    for word in text.split_whitespace() {
        let pig_latinize = to_pig_latin(word);
        output.push(pig_latinize);
    }
    output.join(" ")
}

fn main() {
    println!("{}", pig_latinize("first hello world how are you"));
}
