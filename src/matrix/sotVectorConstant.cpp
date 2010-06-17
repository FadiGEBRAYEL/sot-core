/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      sotVectorConstant.cp
 * Project:   SOT
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <sot-core/sotVectorConstant.h>

#include <sot-core/factory.h>
SOT_FACTORY_ENTITY_PLUGIN(sotVectorConstant,"VectorConstant");

using namespace std;


/* --------------------------------------------------------------------- */
/* --- VECTOR ---------------------------------------------------------- */
/* --------------------------------------------------------------------- */
void sotVectorConstant::
commandLine( const std::string& cmdLine,
	     std::istringstream& cmdArgs, 
	     std::ostream& os )
{
  if( cmdLine == "resize" )
    {
      cmdArgs >>rows;
      ml::Vector m(rows);
      m.fill(color);
      SOUT.setConstant(m);
    }
  else if( cmdLine == "rand" )
    {
      ml::Vector v(rows);
      for( int i=0;i<rows;++i )
        v(i) = ((rand()+0.0)/RAND_MAX*2)-1.;
      SOUT.setConstant(v);
    }
  else if( cmdLine == "fill" )
    {
      cmdArgs >>color;
      ml::Vector m(rows);
      m.fill(color);
      SOUT.setConstant(m);
    }
  else if( cmdLine == "ping") 
    { SOUT.SignalBase<int>::setReady() ;   }
  else if( cmdLine == "[]" ) 
    {
      unsigned int i; double v;
      cmdArgs >> i;
      ml::Vector m = SOUT.accessCopy();
      if( cmdArgs.good()&&(i>=0)&&i<m.size() )
	{
	  cmdArgs >> v; m(i) = v; /* TODO verif about v? */
	  SOUT.setConstant(m);
	} else { /* TODO: error throw. */ }
    }
  else if( cmdLine == "help" )
    {
      os << "sotVectorConstant"<<endl
	 << "  - resize i \t\t:resize the output to a i vector filled as previously." <<endl
	 << "  - fill x\t\t:fill the vector with <x> value." <<endl
	 << "  - [] i x\t\t:set vector[i] = x."<<endl;
    }
  else Entity::commandLine(cmdLine,cmdArgs,os);
}
