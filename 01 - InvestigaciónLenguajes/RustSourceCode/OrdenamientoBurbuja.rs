use std::time::{SystemTime};

fn bubble_sort(arr: &mut [i32]) {
    let n = arr.len();
    
    let duration_since_epoch_1 = SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).unwrap();
    let duration_since_epoch_2 = SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).unwrap();
    
    // Start timestamp
    let timestamp_nanos_1 = duration_since_epoch_1.as_nanos(); // u128

    for i in 0..n {
        for j in 0..n-i-1 {
            if arr[j] > arr[j+1] {
                arr.swap(j, j+1);
            }
        }
    }

    //End timestamp
    let timestamp_nanos_2 = duration_since_epoch_2.as_nanos(); // u128

    println!("Tardado: {}ns", timestamp_nanos_2-timestamp_nanos_1);
}

fn main() {
    let mut numbers = [90,88,80,76,69,65,51,48,40,22];
    
    println!("Array antes de ordenar: {:?}", numbers);

    
    bubble_sort(&mut numbers);

    println!("Array después de ordenar: {:?}", numbers);
    
}
