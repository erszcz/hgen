package lavrin.hgen.viewer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Viewer extends JFrame
{
  public static void main(String[] args) {
    new Viewer();
  }

  public Viewer() 
  {
    super("Viewer");
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        createAndShowGUI();
      }
    });
    setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
  } // end of Viewer()

  private void createAndShowGUI() {
    Container c = getContentPane();
    c.setLayout( new BorderLayout() );
    ViewerPanel vpanel = new ViewerPanel();
    c.add(vpanel, BorderLayout.CENTER);
    pack();
    setResizable(false);    // fixed size display
    setVisible(true);
  }
}
