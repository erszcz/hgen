interface Heightmap
{
  public void setWrapped(boolean wrap);
  public boolean isWrapped();

  public int getHeight();
  public int getWidth();
  public int getMargin();
  public double getPixel(int x, int y);
  public double getMax();
  public double getMin();

  public boolean setPixel(int x, int y, double value);

  public void flatFill(double v);
  public void randomFill(double min, double max);

  public void clusterFill(double min, double max,
    short clusterChance, short radius);

  public void clusterFilter(int radius);

  public void alternateClusterFilter(short radius);

  public void liquidFilter(double c, double d, double t, double u);

  public void smoothFilter(short radius);
  public void terraceFilter(short levels);

  public void walkerFilter(int incStep, int decStep);

  public void faultingFilter(int incStep, int decStep);

  public void normalize();
  public void normalize(double max, double min);

  public boolean hasMask();
}
