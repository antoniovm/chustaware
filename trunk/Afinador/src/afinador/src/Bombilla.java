package afinador.src;

import java.awt.Graphics;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

public class Bombilla extends JComponent {
	
	private boolean on;
	private ImageIcon imagenOn, imagenOff;
	
	public Bombilla() {
		on = false;
		imagenOn = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"on.gif");
		imagenOff = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"off.gif");
	}
	
	public void paintComponents(Graphics g) {
		super.paintComponents(g);
		
		if (on) {
			g.drawImage(imagenOn.getImage(), 0, 0, imagenOn.getIconWidth(), imagenOn.getIconHeight(), this);
		} else {
			g.drawImage(imagenOff.getImage(), 0, 0, imagenOff.getIconWidth(), imagenOff.getIconHeight(), this);
		}
	}

	public boolean isOn() {
		return on;
	}

	public void setOn(boolean on) {
		this.on = on;
	}

	public ImageIcon getImagenOn() {
		return imagenOn;
	}

	public void setImagenOn(ImageIcon imagenOn) {
		this.imagenOn = imagenOn;
	}

	public ImageIcon getImagenOff() {
		return imagenOff;
	}

	public void setImagenOff(ImageIcon imagenOff) {
		this.imagenOff = imagenOff;
	}
	
	

}
