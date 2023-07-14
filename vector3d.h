typedef float f;

class vector3d{
public:
    f x,y,z;
    vector3d(){
        x=0;
        y=0;
        z=0;
    }

    vector3d(f x1,f y1,f z1=0){
        x=x1;
        y=y1;
        z=z1;
    }
    vector3d(const vector3d &vec);    //copy constructor
    vector3d operator+(const vector3d &vec);    //addition
    vector3d &operator+=(const vector3d &vec);  ////assigning new result to the vector
    vector3d operator-(const vector3d &vec);    //substraction
    vector3d &operator-=(const vector3d &vec);  //assigning new result to the vector
    vector3d operator*(float value);    //multiplication
    vector3d operator*(const vector3d &vec);    //multiplication
    vector3d &operator*=(float value);  //assigning new result to the vector.
    vector3d operator/(float value);    //division
    vector3d &operator/=(float value);  //assigning new result to the vector
    vector3d &operator=(const vector3d &vec);
    float dot_product(const vector3d &vec); //scalar dot_product
    vector3d cross_product(const vector3d &vec);    //cross_product
    float magnitude();  //magnitude of the vector
    vector3d normalize();   //nor,malized vector
    float square(); //gives square of the vector

    float distance(const vector3d &vec);    //gives distance between two vectors
    float getX(); //return x
    float getY(); //return y
    float getZ(); //return z
    void print(); //display value of vectors
};