#include "universe.h"

Universe::Universe()
{
    gravitational_const = G;
    
    /* Set up timing, 1 second */
    time_increment = (double)1/48;
    setTimeSpeed( 1 );
    timer = SDL_AddTimer( (time_increment * 1000) / time_speed, Universe::callUpdateTime, this );

    masses.clear();
		lights.clear();
}


Universe::~Universe()
{
  for( vector<Mass *>::iterator it = masses.begin(); it < masses.end(); it++ )
    delete *it;

  for( vector<LightSource *>::iterator it = lights.begin(); it < lights.end(); it++ )
    delete *it;
		
  SDL_RemoveTimer( timer );
}


Uint32 Universe::callUpdateTime( Uint32 interval, void *arg )
{
  Universe *obj = (Universe *)arg;
  ++(*obj);

  return obj->time_update_interval;
}

void Universe::operator++()
{
  applyGravity();
  
  /* Update positions */
  vector<Mass *>::iterator it;
  for( it = masses.begin(); it < masses.end(); it++ )
    (*it)->increment( time_increment );
}


void Universe::draw()
{
  vector<void *>::iterator it;

  for( vector<LightSource *>::iterator it = lights.begin(); it < lights.end(); it++ )
    ((LightSource *)*it)->place();

  for( vector<Mass *>::iterator it = masses.begin(); it < masses.end(); it++ )
    ((Mass *)*it)->draw();
}


void Universe::gravitate( Mass *arg1, Mass *arg2 )
{
  vector<COOR_TYPE> temp, temp2;
  vector<COOR_TYPE> dist;
  float             d = 0,f1,f2;

  temp = arg1->getLocation();
  temp2 = arg2->getLocation();
  dist.resize(3,0);

  for( int i = 0; i < 3;i++ )
  {
    dist[i] = temp2[i] - temp[i];

    d += dist[i] * dist[i];
  }

  /* f = Gmm/r^2 */
  f1 = ( arg1->getMass() ? G*arg2->getMass()/d : 0 );
  f2 = ( arg2->getMass() ? G*arg1->getMass()/d : 0 );
    
  for( int i = 0; i < 3; i++ )
  {
    temp[i] = (( dist[i] >= 0 )?1:-1) * abs(dist[i]/sqrt(d))*f1;
    temp2[i] = (( dist[i] >= 0 )?-1:1) * abs(dist[i]/sqrt(d))*f2;
  }

  arg1->accelerate( temp );
  arg2->accelerate( temp2 );
}


void Universe::applyGravity()
{
  vector<Mass *>::iterator it, it2;
  
  for( it = masses.begin(); it < masses.end() - 1; it++ )
    for( it2 = it + 1; it2 < masses.end(); it2++ )
      gravitate( *it, *it2 );
}


void Universe::addLight( LightSource *arg )
{
	lights.push_back( arg );
}


void Universe::addMass( Mass *arg )
{
    masses.push_back( arg );
}


void Universe::addMass( Mass *arg, LightSource *arg2 )
{
    masses.push_back( arg );
		
		arg2->attach( arg );
		lights.push_back( arg2 );
}


Mass* Universe::getMass( const int arg )
{
  return masses[arg];
}


void Universe::setTimeSpeed( double arg )
{
  time_speed = arg;
  
  /* Update update interval which is in millseconds */
  time_update_interval = (time_increment * 1000) / time_speed;
}
