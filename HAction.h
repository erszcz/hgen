#ifndef HACTION_H
#define HACTION_H

// w przyszlosci to moznaby to zamienic na klase
// z akcesorami sprawdzajacymi zakresy dla odpowiednich wartosci
// (w stylu takim, zeby nie przyjmowalo ujemnych czasow, etc)
// ...wystarczy dopisac sprawdzanie zakresow i wyjatki :)

class HAction
{
  public:
  enum Type
  {
    none,
    randomFill,
    clusterFill,
    clusterFilter,
    alternateClusterFilter,
    liquidFilter,
    smoothFilter,
    walkerFilter,
    faultingFilter
  };

  private:
  Type _type;
  
  // general
  int    _width;
  int    _height;
  int    _margin;
  double _minimum;
  double _maximum;
  short  _chance;
  int    _radius;
  int    _iterations;
  bool   _wrap;

  // fluid simulation
  double _waveSpeed;    // c
  double _nodeDistance; // d
  double _timeStep;     // t
  double _viscosity;    // u

  // random walkers / faulting (last 2)
  int _incStep;
  int _decStep;

  public:
  HAction()
    : _type(none),
      _width(0),
      _height(0),
      _margin(0),
      _minimum(0.),
      _maximum(0.),
      _chance(0),
      _radius(0),
      _iterations(0),
      _wrap(false),
      _waveSpeed(0.),
      _nodeDistance(0.),
      _timeStep(0.),
      _viscosity(0.),
      _incStep(0),
      _decStep(0)
  {
    _iterations = 0;
  }

  Type type() {return _type;}
  void setType(Type type) {this->_type = type;}

  // general getters
  int width()      {return _width;}
  int height()     {return _height;}
  int margin()     {return _margin;}
  double minimum() {return _minimum;}
  double maximum() {return _maximum;}
  short chance()   {return _chance;}
  int radius()     {return _radius;}
  int iterations() {return _iterations;}
  bool wrap()      {return _wrap;}

  // general setters
  void setWidth(int width)      {this->_width = width;}
  void setHeight(int height)    {this->_height = height;}
  void setMargin(int margin)    {this->_margin = margin;}
  void setMinimum(int minimum)  {this->_minimum = double(minimum);}
  void setMaximum(int maximum)  {this->_maximum = double(maximum);}
  void setChance(int c)         {this->_chance = c;}
  void setRadius(int radius)    {this->_radius = radius;}
  void setIterations(int iters) {this->_iterations = iters;}
  void setWrap(bool wrap)       {this->_wrap = wrap;}

  // fluid simulation getters
  double waveSpeed()    {return _waveSpeed;}
  double nodeDistance() {return _nodeDistance;}
  double timeStep()     {return _timeStep;}
  double viscosity()    {return _viscosity;}

  // fluid simulation setters
  void setWaveSpeed(int speed)   {this->_waveSpeed = double(speed);}
  void setNodeDistance(int dist) {this->_nodeDistance = double(dist);}
  void setTimeStep(double step)  {this->_timeStep = step;}
  void setViscosity(int v)       {this->_viscosity = double(v);}

  // random walkers / faulting getters
  int incStep() {return _incStep;}
  int decStep() {return _decStep;}

  // random walkers / faulting setters
  void setIncStep(int incStep) {this->_incStep = incStep;}
  void setDecStep(int decStep) {this->_decStep = -decStep;}
};

#endif
