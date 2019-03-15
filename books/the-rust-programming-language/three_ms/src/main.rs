use std::collections::HashMap;

fn mean(lst: &[i32]) -> i32 {
    let mut sum = 0;
    for elem in lst {
        sum += elem;
    }
    sum/(lst.len() as i32)
}

fn median(lst: &[i32]) -> i32 {
    let mut v = vec![0; lst.len()];
    v.copy_from_slice(lst);
    v.sort_unstable();
    if v.len()%2 == 0 {
        (v[v.len()/2 - 1] + v[v.len()/2])/2
    } else {
        v[v.len()/2]
    }
}

fn mode<T: std::cmp::Eq + std::hash::Hash>(lst: &[T]) -> &T {
    let mut h = HashMap::new();
    for val in lst {
        let count = h.entry(val).or_insert(0);
        *count += 1;
    }
    let mut max_key = &lst[0];
    let mut max_count = 0;
    for (key, count) in h {
        if count > max_count {
            max_key = key;
            max_count = count;
        }
    }
    max_key
}

fn main() {
    let list: Vec<i32> = vec![1, 1, -9, 7, 5, 10, -1324, 1, 543, 0, 2, 7, 6340, -1, 1];
    let mn = mean(&list);
    let mdn = median(&list);
    let md = mode(&list);

    println!("Mean: {}, median: {}, mode: {}.", mn, mdn, md);
}
