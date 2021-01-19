#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include<iostream>

using namespace::std;

int main(){

    // Basic example of cpp (math)
	float a = 1.0, b = 2.0;
	cout << "Basic example of cpp: " << endl;
	cout << "sqrt(a): " << sqrt(a) << endl;
	cout << "sqrt(b): " << sqrt(b) << endl;
	cout << "acos(-1) [arccos(-1)]: "<< acos(-1) << endl;
	cout << "sin(30): " << sin(30.0 / 180.0 * acos(-1));
	// sqrt(b) : 1.41421
	// acos(-1)[arccos(-1)] : 3.14159
    // sin(30) : 0.5


	// Basic example of vector (eigen)
	cout << "Basic example of vector" << endl;

	Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
	Eigen::VectorXf w(3);
	w(0) = 1.0f; w(1) = 0.0f; w(2) = 0.0f;

	cout << "Example output of v: " << endl << v << endl;
	//Example output of v:
	// 1
	// 2
	// 3
	cout << "Example output of add two vectors: " << endl << v + w << endl;
	//Example output of add two vectors:
	// 2
	// 2
	// 3

	// vector scalar multiply
	cout << "Example output of do vector scalar multiply: (v * 3) "<< endl << v * 3.0f << endl;
	// Example output of do vector scalar multiply : (v * 3)
	// 3
	// 6
	// 9

	// dot product and cross product
	cout << "Dot product: v * w:  " << v.dot(w) << endl;
	Eigen::Vector3d v1(1.0, 2.0, 3.0);
	Eigen::Vector3d v2(1.0, 3.0, 3.0);
	cout << "Cross product v1 x v2: " << endl << v1.cross(v2) << endl;
	// Dot product : v * w : 1
	// Cross product v1 x v2 :
	// -3
	// 0
	// 1


	// Basic example of matrix
	cout << "Basic example of matrix" << endl;
	// define a Nonsquare Matrix
	Eigen::MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	cout << "Here is the matrix m: " << endl << m << endl;
	// Here is the matrix m :
	// 3   -1
    // 2.5 1.5

	// resizing
	m.resize(4, 3);
	// matrix will be initialized into a new matrix with 4 rows and 3 cols
	cout << "m.rows(): " << m.rows() << endl; // 4
	cout << "m.cols(): " << m.cols() << endl; // 3

	m.resize(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);

	Eigen::Matrix2d n;
	n << 1, 2,
		3, 4;
	cout << "Here is the matrix n: " << endl << n << endl;
	// Here is the matrix n :
	// 1 2
    // 3 4

	Eigen::Vector2d vd(1, 2);
	cout << "n * vd: " << endl << n * vd << endl;
	//  5
	// 11
	cout << "m * n: " << endl << m * n << endl;
	// m * n:
	// 0  2
	// 7 11
   
    cout << "Test1: " << endl;
    Eigen::Vector4d v4(1.9, 2.8, 3.4, 3.9);

    cout << v4.head<3>() << endl;;

    cout << "Test2: " << endl;
    cout << v4.data() << endl;;


    

    // Exercise: (Assignment0)
    // Jiawei Wang 20201222
    
    Eigen::Vector3d p(2, 1, 1);
    // The transformation matrix: (45 degrees counter-clockwise && (1, 2))
    
    Eigen::Matrix3d tf;

    tf << 1/sqrt(2), -1/sqrt(2), 2,
       1/sqrt(2), 1/sqrt(2), 1,
       0, 0, 1;

    cout << "Answer: " << endl << tf * p << endl;

    // Answer:
    // 2.70711
    // 3.12132
    // 1
    
    return 0;



}
