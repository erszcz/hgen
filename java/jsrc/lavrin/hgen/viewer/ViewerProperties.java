package lavrin.hgen.viewer;

import java.awt.*;
import java.util.*;
import java.io.*;


public class ViewerProperties
{
  private static final String PROP_FNM = "viewer_props.txt";
  // where the property key=value pairs are stored

  private Properties viewerProps;


  public ViewerProperties()
  {
    loadProperties();
    listProperties();
  }


  private void loadProperties()
    // load the properties from the PROP_FNM file
  {
    viewerProps = new Properties();
    try {
      FileInputStream in = new FileInputStream(PROP_FNM);
      viewerProps.load(in);
      in.close();
      System.out.println("Loaded properties from " + PROP_FNM);
    } 
    catch (IOException e) {
      System.out.println("Could not load properties from " + PROP_FNM);
    }
  }


  private void listProperties()
  {
    if (viewerProps.isEmpty())
      System.out.println("No properties in " + PROP_FNM);
    else {
      System.out.println("Properties in " + PROP_FNM);
      viewerProps.list(System.out);
    }
  }


  public boolean isFullScreen()
    /* return the fullscreen string value (true or false)
       as a boolean; the default is false */
  {
    String prop;
    if ((prop = viewerProps.getProperty("fullscreen")) != null)
      return Boolean.valueOf(prop);
    else {
      System.out.println("No 'fullscreen' property found; using false");
      return false;
    }
  }


  public void setFullScreen(boolean b)
    /* store the fullscreen boolean as a string */
  {
    viewerProps.setProperty("fullscreen", Boolean.toString(b));
  }


  public String getRecipe()
  {
    String prop;
    if ((prop = viewerProps.getProperty("recipe")) != null)
      return prop;
    else {
      System.out.println("No 'recipe' property found; using 'hmap.csv'");
      return "hmap.csv";
    }
  }


  public void setRecipe(String recipe)
  {
    viewerProps.setProperty("recipe", recipe);
  }


  public String getControls()
  {
    String prop;
    if ((prop = viewerProps.getProperty("controls")) != null) {
      if (! (prop.equals("mouse") || prop.equals("keys"))) {
        String err = 
          "Unknown 'controls' property value %s. Falling back to 'mouse'.\n";
        System.out.printf(err, prop);
        return "mouse";
      }
      return prop;
    } else {
      System.out.println("No 'controls' property found; using 'mouse'");
      return "mouse";
    }
  }


  public void setControls(String controls)
  {
    viewerProps.setProperty("controls", controls);
  }


  public void saveProperties()
    // save the properties to the PROP_FNM file
  {
    listProperties();

    try {
      FileOutputStream out = new FileOutputStream(PROP_FNM);
      viewerProps.store(out, "Properties");
      out.close();
      System.out.println("Saved properties in " + PROP_FNM);
    } 
    catch (IOException e) {
      System.out.println("Could not save properties in " + PROP_FNM);
    }
  }
}
