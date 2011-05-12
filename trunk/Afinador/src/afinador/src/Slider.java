package afinador.src;

import java.awt.Dimension;
import java.awt.Graphics;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

public class Slider extends JComponent {
	private int offset;
	private ImageIcon barra, pua;
	
	public Slider(){
		offset=0;
		barra = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"barraSlider.png");
		pua = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"puaCW.png");
		try{
			this.setPreferredSize(new Dimension(barra.getIconWidth(), pua.getIconHeight()));
		} catch (Exception e) {
			System.out.println("No se encuentran las imágenes");
		}
		setUI(null);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if(offset == 0){
			g.drawImage(barra.getImage(), 0, getHeight()/2, barra.getIconWidth(), barra.getIconHeight(), this);
			g.drawImage(pua.getImage(), this.getWidth()/2-pua.getIconWidth()/2, 0, pua.getIconWidth(), pua.getIconHeight(), this);
		}
	}
	
	public int getOffset() {
		return offset;
	}

	public void setOffset(int offset) {
		this.offset = offset;
		repaint();
	}

	public ImageIcon getBarra() {
		return barra;
	}

	public void setBarra(ImageIcon barra) {
		this.barra = barra;
	}

	public ImageIcon getPua() {
		return pua;
	}

	public void setPua(ImageIcon pua) {
		this.pua = pua;
	}
}
