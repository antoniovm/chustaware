package afinador.src;
/**
 * 	Clase que se encarga de comparar valores del array de frecuencias con las frecuencias fundamentales(notas)
 */
public class Afinador {
	//señal de entrada
	double [] frecuencia;
	//OCTAVA primera(Hz): Do,Do#,Re,Re#,Mi,Fa,Fa#,Sol,Sol#,La,La#,Si 
	double [] notas={32.7, 34.65, 36.71, 38.89, 41.2, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};
	double pitch;
	private boolean afinando;
	
	public Afinador(double [] frecuencia) {
		this.frecuencia=frecuencia;
	}
	public void afinar(){
		afinando=true;
		int max=0;
		while(afinando){
			for (int i = 1; i < frecuencia.length; i++) {
				if(frecuencia[i]-frecuencia[i-1] > 10)
					max=i;
			}
			
		}
	}
}
