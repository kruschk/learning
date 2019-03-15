use std::default::Default;
use std::ops::Add;

#[derive(Debug)]
struct Point2D<T> {
    x: T,
    y: T,
}

impl<T> Point2D<T> {
    pub fn new(x: T, y: T) -> Point2D<T> {
        Point2D {
            x,
            y,
        }
    }
}

impl<T: Add> Point2D<T> {
    fn add(self, other: Point2D<T>) -> Point2D<<T as Add>::Output> {
        Point2D {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

impl<T: Add> Add for Point2D<T> {
    type Output = Point2D<<T as Add>::Output>;

    fn add(self, other: Point2D<T>) -> Self::Output {
        Point2D {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

fn main() {
    let x: f64 = Default::default();
    println!("{}", x);
    println!("{}", <f64 as Default>::default());
    let p1 = Point2D { x: 0.3, y: 1.9};
    let p2 = Point2D { x: 1.5, y: -1.8};
    println!("{:?}", p1 + p2);
    //println!("{:?}", p1.add(p2));
}