/*************************************************
*                                                *
* 
*  Gravitational lensing made simple
*
*  By Antonio Herrera
*
*
*
*
*

*                                                *
*************************************************/

#include "EasyBMP.h"
#include <math.h>
using namespace std;


float alphafunc(float theta, float Dos, float Dls, float Dol)
{
  float alpha;
  float M,critden;
  float sigma;
  float thetaE;
  //MODELS TO SELECT

  // Point mass lens

  // Mass can inputed as kpc or solar masses
   
  //M = 1e12  ;// In solar masses
  //M = M * 4.8612e-17;    // converting to Kpc

    M = 12.5 ; // In Kpc
    
    alpha = 4.0*(Dos/(Dol*Dls))*M;
 
    alpha = alpha/theta;
 
 //Singular Isothermal Sphere
  //sigma = 3;
  //M = 3.1416*pow(sigma,2)*Dol*theta;
  //critden = Dos/(4*3.1416*Dol*Dls);
  //alpha = M/(3.1416*Dol*Dol*critden*theta); 
  //thetaE = 10;
  //alpha = thetaE*theta/abs(theta);
    
 return alpha;
}


int main( int argc, char* argv[] )
{
 cout << endl
      << "Using EasyBMP Version " << _EasyBMP_Version_ << endl << endl
      << "Copyright (c) by the EasyBMP Project 2005-6" << endl
      << "WWW: http://easybmp.sourceforge.net" << endl << endl;
 
 int x,y, i,j, height, width, y0,x0,xout,yout; 

 float gamma,gamma2,alpha, beta;
 float theta, Dol, Dos, Dls,  ratio;


 /***************************
 *    Information of the lens
 *****************************/

 
 // Ratio between kpc and pixels

 ratio =  1; // rad/pix

 
 y0 = 50;//47;//height/2;
 x0 = 45;//57; //width /2;


 /***************************
 *    Information of files
 *****************************/
 BMP AnEmpty;

 AnEmpty.SetSize(100,100);

 BMP AnInput;
 AnInput.ReadFromFile("spheralsource.bmp");

 BMP AnOutput;
 AnOutput.ReadFromFile("Pointlens.bmp");

 height = AnInput.TellHeight() - 1;
 width = AnInput.TellWidth() - 1;

 /***************************
 *    Information of the model and geometry
 *
 * The equation code is worked in geometrical units
 * G = c = 1
 *****************************/
 
 //Geometry of the distance.
 
 Dol = 1;  // Units are in kpc
 Dls = 1;
 Dos = Dol+Dls ; //This is not entirely true, but good approximation
 


 
   

 /***************************
 *   Lens simulation
 *****************************/



 cout << "The center of the lens is "<<"(" << x0 << "," << y0<< ")" << endl;
 cout << "The size of the image is "<< height + 1 << "px X " << width + 1 << "px" <<endl;
 RGBApixel Temp = AnInput.GetPixel(0,0);
 RGBApixel Temp2 = AnOutput.GetPixel(0,0);
 RGBApixel Temp3 = AnOutput.GetPixel(0,0);
 
 cout << "Image position" <<" | " << " reference to lens " <<"| " << " beta " << endl; 
 for (i=0; i< width + 1; i++ ){
   for (j = 0; j < height + 1; j++ ){
     x = i - x0; 
     y = y0 - j;
     theta = ratio*sqrt(pow(x,2)+pow(y,2)); // theta is in rad
     if( theta != 0 )
       {
	 beta = theta - alphafunc(theta, Dos, Dls, Dol);

     

	 //cout << "(" << x << "," << y << ")" << endl;
     //cout << "The value of beta = " << beta << endl;
	 gamma = (float)y/x ;  // Here the pix ratio is irrelevant
	 gamma2 = atan2(y,x);    // because it is an angle to position in the image
     
	 yout = round(sin(gamma2)*beta/ratio) ; 
	 xout = round(cos(gamma2)*beta/ratio) ; 

	 yout = y0 - yout;
	 xout = xout + x0;
     //cout << "(" << xout << "," << yout << ")" << endl;
     //cout << "The value of Tan (Gamma) = "   << gamma << endl;
     // cout << "The value of atan2 =" << gamma2 << endl;
     //cout << "Sin gamma = " << sin(gamma2) << endl;
     // cout << "Output y = " << y << endl;
     //cout << "Output x = " << x << endl; 

     //cout << "(" << (int) Temp.Red << ","
     //  << (int) Temp.Green << ","
     //	  << (int) Temp.Blue << ","
     //	  << (int) Temp.Alpha << ")" << endl;
    
	 //if( (i<60) && (j <60) )
	 //  {
	      cout << "("<< i <<"," << j << ")" ;
	      cout.width(15);
	      //    cout <<" " <<  sin(gamma2)*beta ;
	      cout << "("<< x <<"," << y << ")" ;
	      //cout << "("<< xout <<"," << yout << ")" ;
	      cout.width(15);
	      cout <<" " <<beta << endl ;
	      //  }
     // Change this pixel to a blue-grayish color
     //Temp.Red = 255; Temp.Green = 50; Temp.Blue = 192; Temp.Alpha = 0;
     //AnOutput.SetPixel(x,y,Temp);
	 if ((xout > width) or (yout > height) or (xout < 0) or (yout < 0)) 
	   { continue ; }
	 else {
	  
	   Temp = AnInput.GetPixel(xout,yout);
	   Temp2 = AnOutput.GetPixel(i,j);
	   //if ( (Temp2.Red == 255) and (Temp2.Green == 255) and (Temp2.Blue == 255) )
	   // {
	       AnOutput.SetPixel(i,j,Temp);
	       AnEmpty.SetPixel(i,j,Temp);
	       //  }
	 }
       }
     else
       {
	 //cout << "The value of theta is " << theta << endl;
	 //cout << "The position is ( " << i << " , " << j << " ) " << endl; 
	 Temp2 = AnOutput.GetPixel(i,j);
	 if ( (Temp2.Red == 255) and (Temp2.Green == 255) and (Temp2.Blue == 255) )
	   {
	     Temp = AnInput.GetPixel(i,j);
	     AnOutput.SetPixel(i,j,Temp);
	     AnEmpty.SetPixel(i,j,Temp);
	   }
       }
   }
 }

 // Set visually position of point lens
 Temp = AnOutput.GetPixel(x0,y0);
 Temp.Red = 255;
 Temp.Green = 0;
 Temp.Blue = 0;
 AnOutput.SetPixel(x0,y0,Temp);


   // write output
 AnOutput.WriteToFile( "pointlensG3.bmp" );
 AnEmpty.WriteToFile("fromempy.bmp");

 //Temp = AnInput.GetPixel(0,0);
 //cout << "(" << (int) Temp.Red << ","
 //     << (int) Temp.Green << ","
 //     << (int) Temp.Blue << ","
 //    << (int) Temp.Alpha << ")" << endl;

 //cout << "(" << AnOutput.TellWidth() << ","
 //    << AnOutput.TellHeight() << ")" <<endl;
 
 // for (i = 0; i < 4; i++){
 // cout << i;
 //}
 
 return 0;
}
