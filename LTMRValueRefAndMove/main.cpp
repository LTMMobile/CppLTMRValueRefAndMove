//
//  main.cpp
//  LTMRValueRefAndMove
//
#include <iostream>
using namespace std;

class Point {
public:
    double x = 0.0;
    double y = 0.0;
    
    Point( double xx, double yy ) : x(xx), y(yy) {}
};

class Segment {
private:
    Point * p1, * p2;
public:
    Segment( const Point& pp1, const Point& pp2 ) :
                p1(new Point(pp1)), p2(new Point(pp2)) {
    }
    
    Segment( const Segment& cs ) {
        p1 = new Point(*cs.p1);
        p2 = new Point(*cs.p2);
    }
    
    Segment( Segment&& cs ) { // move constructor
        p1 = cs.p1;
        p2 = cs.p2;
        
        cs.p1 = nullptr;
        cs.p2 = nullptr;
    }
    
    Segment& operator = (const Segment& is) {
        if( this != &is ) {
            *p1 = *is.p1;
            *p2 = *is.p2;
        }
        
        return *this;
    }
    
    Segment& operator = (Segment&& cs) { // move operator
        
        if( this != &cs ) {
            delete p1;
            delete p2;
            
            p1 = cs.p1;
            p2 = cs.p2;
            
            cs.p1 = nullptr;
            cs.p2 = nullptr;
        }
        
        return *this;
    }
    
    Segment clone() {
        Segment s(*this);
        return s;
    }
    
    void printAddress() {
        cout << "objet = " << this << ", p1 = " << p1 << ", p2 = " << p2 << endl;
    }
    
    ~Segment() {
        if( p1 ) {
            delete p1;
            p1 = nullptr;
        }
        if( p2 ) {
            delete p2;
            p2 = nullptr;
        }
    }
};

int main(int argc, const char * argv[]) {

    //case 1
    Segment s1( Point(1.2, 3.4), Point(3.4, 8.9) );
    // assertion vérifiant que s1 est correct
    s1.printAddress();
    
    // case 2
    Segment s2( s1 );
    s2.printAddress();
    
    // case 3 operator fonctionnement de base
    s1 = s2; // call operator =
    // assertion
    
    // case 4 : test du std::move sur l'affectation
    s1 = std::move(s2); // call move operator =
    // assertion: s1 <- s2, s2 invalide
    
    Segment s3( std::move(s1) ); // move ctor
    s3.printAddress();
    
    s2 = s3.clone(); // call move operator =
    
    return 0;
}









