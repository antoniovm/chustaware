package afinador.src;
/**
 * 	Clase que se encarga de comparar valores del array de frecuencias con las frecuencias fundamentales(notas)
 */
public class Afinador {
	//se�al de entrada
	private double [] frecuencia;
	//Primera Octava (Hz):    Do     Do#    Re     Re#    Mi    Fa     Fa#    Sol   Sol#   La     La#    Si 
	private double [] notas={32.7, 34.65, 36.71, 38.89, 41.2, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};
	private int pitch, notaReal, octava;
	private double desafinio;
	private boolean afinando;
	
	public Afinador(double [] frecuencia) {
		this.frecuencia=frecuencia;
	}
	public double[] getFrecuencia() {
		return frecuencia;
	}
	public void setFrecuencia(double[] frecuencia) {
		this.frecuencia = frecuencia;
	}
	public double[] getNotas() {
		return notas;
	}
	public void setNotas(double[] notas) {
		this.notas = notas;
	}
	public int getPitch() {
		return pitch;
	}
	public void setPitch(int pitch) {
		this.pitch = pitch;
	}
	public int getNotaReal() {
		return notaReal;
	}
	public void setNotaReal(int notaReal) {
		this.notaReal = notaReal;
	}
	public int getOctava() {
		return octava;
	}
	public void setOctava(int octava) {
		this.octava = octava;
	}
	public double getDesafinio() {
		return desafinio;
	}
	public void setDesafinio(double desafinio) {
		this.desafinio = desafinio;
	}
	public boolean isAfinando() {
		return afinando;
	}
	public void setAfinando(boolean afinando) {
		this.afinando = afinando;
	}
	public void afinar(){
		afinando=true;
		int max=0;
		while(afinando){
			for (int i = 1; i < 4500; i++) {
				if(frecuencia[i]>frecuencia[max])
					max=i;
			}
			pitch=max;
			calcularNota();
			
		}
	}
	
	private void calcularNota() {
		int exceso=Integer.MAX_VALUE, defecto=Integer.MIN_VALUE, octavaExceso=0,octavaDefecto=0, notaExceso=-1, notaDefecto=-1;
		for (int i = 0; i < notas.length; i++) {
			if((pitch%notas[i])<exceso){	//Vemos si esta cerca por encima de la nota
				exceso=(int)(pitch%notas[i]);
				octavaExceso=(int)(pitch/notas[i]);
				notaExceso=i;
			}
			if((pitch%notas[i]-notas[i])>defecto){//Vemos si esta cerca por debajo de la nota
				defecto=(int)(pitch%notas[i]-notas[i]);
				octavaDefecto=(int)(pitch/notas[i]);
				notaDefecto=i;
			}
				
		}
		if(exceso<Math.abs(defecto)){	//El valor mas peque�o de los 2 es el mas cercano
			desafinio=exceso;
			notaReal=notaExceso;
			octava=octavaExceso;
		}else{
			desafinio=defecto;
			notaReal=notaDefecto;
			octava=octavaDefecto;
		}
		
		

	}
}