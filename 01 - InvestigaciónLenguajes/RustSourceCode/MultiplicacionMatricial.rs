
use std::time::{SystemTime};

fn matrix_multiply(a: &[Vec<i32>], b: &[Vec<i32>]) -> Vec<Vec<i32>> {

    let mut result = vec![vec![0; 3]; 3];

    let duration_since_epoch_1 = SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).unwrap();
    let duration_since_epoch_2 = SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).unwrap();
    
        // Timestamp inicio
        let timestamp_nanos_1 = duration_since_epoch_1.as_nanos(); // u128

    for i in 0..3 {
        for j in 0..3 {
            for k in 0..3 {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

        // Timestamp fin
        let timestamp_nanos_2 = duration_since_epoch_2.as_nanos(); // u128
    
    println!["Tardado: {}ns", timestamp_nanos_2-timestamp_nanos_1];

    result
}

fn main() {

    let matrix_a= vec![
        vec![1, 2, 3],
        vec![4, 5, 6],
        vec![7, 8, 9],
    ];

    let matrix_b = vec![
        vec![10, 11, 13],
        vec![12, 13, 14],
        vec![14, 15, 16],
    ];
    
    let result = matrix_multiply(&matrix_a, &matrix_b);

    println!("Resultado:");
    for row in &result {
        println!("{:?}", row);
    }

}
