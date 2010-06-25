/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      derivator.h
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

#include <sot-core/derivator.h>
#include <sot-core/factory.h>

using namespace sot;
using namespace ml;
using namespace dynamicgraph;

#define SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(sotClassType,sotType,className)              \
  template<>                                                                            \
  const double Derivator<sotType>::TIMESTEP_DEFAULT = 1.;                            \
  template<>                                                                            \
  std::string sotClassType<sotType>::                                                   \
  getTypeName( void ) { return #sotType; }                                              \
  template<>                                                                            \
  const std::string sotClassType<sotType>::CLASS_NAME                                   \
     = std::string(className)+"<"+#sotType+">";                                         \
  extern "C" {                                                                          \
    Entity *regFunction##_##sotType##_##sotClassType( const std::string& objname )                    \
    {                                                                                   \
      return new sotClassType<sotType>( objname );                                      \
    }                                                                                   \
  EntityRegisterer regObj##_##sotType##_##sotClassType( std::string(className)+"<"+#sotType+">",      \
					  &regFunction##_##sotType##_##sotClassType );                   \
  }

namespace sot {
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,double,"Derivator");
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,Vector,"Derivator");
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,Matrix,"Derivator");
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,VectorQuaternion,"Derivator");
}

//SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,double,"T");


/*
#define SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(sotClassType,sotType,className,typeName,regFunction,regObj) \
  template<>                                                \
  std::string sotClassType<sotType>::                       \
  getTypeName( void ) { return typeName; }                  \
  template<>                                                \
  const std::string sotClassType<sotType>::CLASS_NAME = std::string(className)+typeName; \
  extern "C" {                                              \
    Entity *regFunction( const std::string& objname )    \
    {                                                       \
      return new sotClassType<sotType>( objname );          \
    }                                                       \
  EntityRegisterer regObj( std::string(className)+typeName,&regFunction );   \
  }


SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,double,"derivator","Double",rfd,rod);
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,ml::Vector,"derivator","Vector",rfv,rov);
SOT_FACTORY_TEMPLATE_ENTITY_PLUGIN(Derivator,ml::Matrix,"derivator","Matrix",rfm,rom);

*/

