fn dot_product(v1: &Vec<f64>, v2: &Vec<f64>) -> Result<f64, ()> {
    if v1.len() != v2.len() {
        return Err(());
    }
    let mut result = 0.0;
    for (x, y) in v1.iter().zip(v2.iter()) {
        result += x*y;
    }
    Ok(result)
}

fn main() {
    let v1 = vec![1.0, 123.4, -17.7, 6.0];
    let v2 = vec![-1.0, 5.678, 9.0, 5.0];
    println!("{}", dot_product(&v1, &v2).unwrap());
}