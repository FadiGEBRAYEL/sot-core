/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      Timer.h
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



#ifndef __SOT_TIMER_HH
#define __SOT_TIMER_HH

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* Classes standards. */
#include <list>                    /* Classe std::list   */
#ifndef WIN32
#include <sys/time.h>
#else  /*WIN32*/
// When including Winsock2.h, the MAL must be included first
#include <MatrixAbstractLayer/boost.h>
#include <sot-core/utils-windows.h>
#include <Winsock2.h>
#endif /*WIN32*/

/* SOT */
#include <dynamic-graph/entity.h>
#include <dynamic-graph/all-signals.h>
#include <sot-core/debug.h>
#include <dynamic-graph/interpreter.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32) 
#  if defined (timer_EXPORTS)
#    define Timer_EXPORT __declspec(dllexport)
#  else  
#    define Timer_EXPORT __declspec(dllimport)
#  endif 
#else
#  define Timer_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */
namespace dg = dynamicgraph;

template< class T >
class Timer_EXPORT Timer
:public dg::Entity
{
 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 protected:
  
  struct timeval t0,t1;
  double dt;

 public:
  
  /* --- CONSTRUCTION --- */
  Timer( const std::string& name );

 public: /* --- DISPLAY --- */
  virtual void display( std::ostream& os ) const;
  Timer_EXPORT friend std::ostream& operator<< ( std::ostream& os,const Timer<T>& timer )
    { timer.display(os); return os; }

 public: /* --- SIGNALS --- */

  dg::SignalPtr<T,int> sigSIN;
  dg::SignalTimeDependent<T,int> sigSOUT;
  dg::Signal<double,int> timerSOUT;


 protected: /* --- SIGNAL FUNCTIONS --- */
  void plug( dg::Signal<T,int> &sig )
    {
      sigSIN = &sig; dt=0.;
    }

  T& compute( T& t,const int& time )
    {
      sotDEBUGIN(15);
      gettimeofday(&t0,NULL);
      sotDEBUG(15) << "t0: "<< t0.tv_sec << " - " << t0.tv_usec << std::endl;
      
      t = sigSIN( time );

      gettimeofday(&t1,NULL);
      dt = ( (t1.tv_sec-t0.tv_sec) * 1000. 
	     + (t1.tv_usec-t0.tv_usec+0.) / 1000. );
      sotDEBUG(15) << "t1: "<< t1.tv_sec << " - " << t1.tv_usec << std::endl;

      timerSOUT = dt;

      sotDEBUGOUT(15);
      return t;
    }

  double& getDt( double& res,const int& time )
    { 
      res=dt; 
      return res;
    }


 public: /* --- COMMANDS --- */
  virtual void commandLine( const std::string& cmdLine,std::istringstream& cmdArgs,
			    std::ostream& os );


};

void cmdChrono( const std::string& cmd,
		std::istringstream& args,
		std::ostream& os );



/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */


/* --- CONSTRUCTION ---------------------------------------------------- */
template< class T >
Timer<T>::
Timer( const std::string& name )
  :Entity(name)
   ,t0(),t1()
   ,dt(0.)
   ,sigSIN( NULL,"Timer("+name+")::output(T)::in" )
   ,sigSOUT(  boost::bind(&Timer::compute,this,_1,_2),
	      sigSIN,
	      "Timer("+name+")::output(T)::out" )
   ,timerSOUT( "Timer("+name+")::output(double)::timer" )
{
  sotDEBUGIN(15);
  timerSOUT.setFunction(  boost::bind(&Timer::getDt,this,_1,_2) );
	      
  signalRegistration( sigSIN<<sigSOUT<<timerSOUT );
  sotDEBUGOUT(15);
}

/* --- DISPLAY --------------------------------------------------------- */
template< class T >
void Timer<T>::
display( std::ostream& os ) const
{
  os << "Timer <"<< sigSIN << "> : " << dt << "ms." << std::endl;
}
/* --- COMMAND --------------------------------------------------------- */
template< class T >
void Timer<T>::
commandLine( const std::string& cmdLine,std::istringstream& cmdArgs,
	     std::ostream& os )
{
  sotDEBUGIN(15);

  if( cmdLine == "help") 
    {
      os << "Timer: "<<std::endl;
      Entity::commandLine( cmdLine,cmdArgs,os );
    }
  else
    Entity::commandLine( cmdLine,cmdArgs,os );
  
  
  sotDEBUGOUT(15);
}



#endif /* #ifndef __SOT_SOT_HH */




