fn main() {
    let day = [
        "first",
        "second",
        "third",
        "fourth",
        "fifth",
        "sixth",
        "seventh",
        "eighth",
        "ninth",
        "tenth",
        "eleventh",
        "twelfth"
    ];
    let lyrics = [
        "a partridge in a pear tree.",
        "two turtle doves",
        "three french hens",
        "four calling birds",
        "five golden rings",
        "six geese a-layin",
        "seven swans a-swimmin",
        "eight maids milkin'",
        "nine lords a-leapin'",
        "ten ladies dancin'",
        "eleven pipers pipin'",
        "twelve drummers drummin'"
    ];
    for num in 1..13 {
        println!("On the {} day of Christmas, my true love gave to me",
                 day[num - 1]);
        for index in (1..num).rev() {
            print!("{}, ", lyrics[index]);
        }
        if num > 1 {
            println!("and {}", lyrics[0]);
        } else {
            println!("{}", lyrics[0]);
        }
    }
}
