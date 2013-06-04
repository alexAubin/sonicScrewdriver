#ifndef Figure_h
#define Figure_h

#include "interface/Common.h" 

using namespace std;

namespace theDoctor
{

    class Figure 
    {
      
     public:
     
      Figure(double value_ = 0, float error_ = 0)
      {
          theValue = value_;
          theError = error_;
      }; 

      ~Figure() { };

      double value() const { return theValue; };
      double error() const { return theError; };
      string Print() const 
      { 
          std::ostringstream s;
          
          s.setf(std::ios::fixed);
          s.precision(2);
          
          s << theValue << " +/- " << theError;
          return s.str();
      }

      Figure operator+(const Figure input) const
      {
            return applyOperation(*this,input,string("add"));
      }
     
      void operator+=(const Figure input)
      {
          Figure newFigure = applyOperation(*this,input,string("add"));
          theValue = newFigure.value();
          theError = newFigure.error();
      }

      Figure operator-(const Figure input) const
      {
            return applyOperation(*this,input,string("substract"));
      }
     
      void operator-=(const Figure input)
      {
          Figure newFigure = applyOperation(*this,input,string("substract"));
          theValue = newFigure.value();
          theError = newFigure.error();
      }

      Figure operator*(const Figure input) const
      {
            return applyOperation(*this,input,string("multiply"));
      }
     
      void operator*=(const Figure input)
      {
          Figure newFigure = applyOperation(*this,input,string("multiply"));
          theValue = newFigure.value();
          theError = newFigure.error();
      }

      Figure operator/(const Figure input) const
      {
            return applyOperation(*this,input,string("divide"));
      }
     
      void operator/=(const Figure input)
      {
          Figure newFigure = applyOperation(*this,input,string("divide"));
          theValue = newFigure.value();
          theError = newFigure.error();
      }


      static Figure applyOperation(const Figure figureA, const Figure figureB, string type)
      {
          TH1F a("a","a",1,-0.5,0.5);
          TH1F b("b","b",1,-0.5,0.5);

        
          a.SetBinContent(1,figureA.value());
          a.SetBinError(1,figureA.error());

          b.SetBinContent(1,figureB.value());
          b.SetBinError(1,figureB.error());
     
               if (type == "add")       a.Add(&b);
          else if (type == "divide")    a.Divide(&b);
          else if (type == "multiply")  a.Multiply(&b);
          else if (type == "substract") 
          {
              b.Scale(-1.0);
              a.Add(&b);
          }


          double newError = 0;
          double newValue = a.IntegralAndError(0,a.GetNbinsX()+1,newError);

          return Figure(newValue,newError);
      }
        

     private:

        double theValue;	
        double theError;

    };

}

#endif