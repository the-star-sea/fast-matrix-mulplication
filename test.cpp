#include "Matrix.h"

int main() {
cout<<"test matrix multiply matrix"<<endl;
    int column1,column2,row1,row2;
    cout << "please input two matrixes:" << endl << "the first Matrix: " << endl << "how many columns?";
    cin >>column1 ;
    while (cin.fail()) {
        cin.clear();
        cin.sync();
        cout << "please check your type." << endl << "retype:";
        cin >> column1;
    }
    cout << "how many rows?";
    cin >> row1;
    while (cin.fail()) {
        cin.clear();
        cin.sync();
        cout << "please check your type." << endl << "retype:";
        cin >> row1;
    }
    cout << "the second Matrix: " << endl << "how many columns?";
    cin >> column2;
    while (cin.fail()) {
        cin.clear();
        cin.sync();
        cout << "please check your type." << endl << "retype:";
        cin >> column2;
    }
    cout << "how many rows?";
    cin >> row2;
    while (cin.fail()) {
        cin.clear();
        cin.sync();
        cout << "please check your type." << endl << "retype";
        cin >> row2;
    }
    if (column1 != row2) {
        cin.clear();
        cin.sync();
        cout << "size donot match";
        main();
        exit(0);
    }
    char g;

    cout << "please input the first Matrix : " << endl;
    float *data1 = new float[column1 * row1];
    float *data2 = new float[column2 * row2];
    for (int i = 0; i < column1 * row1; i++) {
        cin >> data1[i];
        while (cin.fail()) {
            cin.clear();
            cin.sync();
            cout << "please check your type." << endl << "retype from local position:";
            cin >> data1[i];
        }
    }
    cout << "Is it  row-major order?N/the other";
    cin >> g;
    float *s=new float[column1 * row1],*ss=new float[column2*row2];
    if (g == 'N') {
        for (int i = 0; i < column1; i++) {
            for (int j = 0; j < row1; j++) {
                s[i + j * column1] = data1[j + i * row1];
            }
        }
        data1 = s;
    }
    cout << "please input the second Matrix : " << endl;
    for (int i = 0; i < column2 * row2; i++) {
        cin >> data2[i];
        while (cin.fail()) {
            cin.clear();
            cin.sync();
            cout << "please check your type." << endl << "retype from local position:";
            cin >> data2[i];
        }
    }
    cout << "Is it  column-major order?N/the other";
    cin >> g;
    if (g == 'N') {
        for (int i = 0; i < column2; i++) {
            for (int j = 0; j < row2; j++) {
                ss[j + i * row2] = data2[i + j * column2];
            }
        }
        data2 = ss;
    }


    Matrix *matrix1=new Matrix(column1,row1,data1), *matrix2=new Matrix(column2,row2,data2);
    Matrix *ans = new Matrix(column2, row1, new float[row1 * column2]);
    *ans = *matrix1 * *matrix2;
    cout << *ans;int j;
    cout<<"test number multiply matrix and matrix multiply scaler and scaler multiply matrix"<<endl<<"input an float: ";
    cin >> j;
    while (cin.fail()) {
        cin.clear();
        cin.sync();
        cout << "please check your type." << endl << "retype :";
        cin >> j;
    }
    cout<<*ans<<"*"<<j<<"="<<*ans*j<<endl<<j<<"*"<<*ans<<"="<<j**ans;


delete ans;delete matrix1;delete matrix2;

}
