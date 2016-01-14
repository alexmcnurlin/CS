// Name:  Alex McNurlin
// Class: CS120-04
// Lab:   Lab 12
// Date:  Tue Nov 17 12:35:56 PST 2015

#include <iostream>
using namespace std;

// Declare the color class here...
class color {
  public:
    color(){
      r=0;
      g=0;
      b=0;
    };
    color(int red, int green, int blue){
      r=red;
      g=green;
      b=blue;
    };
    void set(int red, int green, int blue);
    void mix(const color &c);
    void add(const color &c);
    int R() const;
    int G() const;
    int B() const;
  private:
    int r;
    int g;
    int b;
};

// Put definitions for the color class methods here...
void color::set(int red, int green, int blue) {
  r=red;
  g=green;
  b=blue;
};

void color::mix(const color &c){
  r=(r+c.R())/2;
  g=(g+c.G())/2;
  b=(b+c.B())/2;
};

void color::add(const color &c){
  r=max(r,c.R());
  g=max(g,c.G());
  b=max(b,c.B());
};

int color::R() const{
  return r;
};
int color::G() const{
  return g;
};
int color::B() const{
  return b;
};


int max(int a, int b);

int main() {
  const color Black;
  const color White( 255, 255, 255 );
  const color SkyBlue( 135, 206, 235 );
  const color SeaGreen( 46, 139, 87 );
  const color Gold( 255, 215, 0 );
  const color Chocolate( 210, 105, 30 );
  const color DarkGrey( 75, 75, 75 );

  color Custom( White );
  Custom.mix( DarkGrey );
  Custom.mix( SkyBlue );

  color CreamyMix( White );
  CreamyMix.mix( SkyBlue );
  CreamyMix.mix( SeaGreen );
  CreamyMix.mix( White );
  CreamyMix.mix( White );

  color mixes[5];
  mixes[0] = SkyBlue;
  mixes[0].add( SeaGreen );
  mixes[0].mix( Black );

  mixes[1].set( Chocolate.B(), SeaGreen.R(), DarkGrey.G() );
  mixes[1].mix( Gold );

  mixes[2] = White;
  mixes[2].add( Black );
  mixes[2].add( Gold );

  mixes[3].set( Chocolate.R(), Gold.G(), SeaGreen.B() );
  mixes[3].add( SkyBlue );

  mixes[4] = mixes[3];
  mixes[4].mix( Black );
  mixes[4].mix( Black );
  return Black.R();
}

int max(int a, int b) {
  return (a<b)?b:a;
}
