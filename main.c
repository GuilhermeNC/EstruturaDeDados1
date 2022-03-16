#include <stdio.h>
#include <stdlib.h>
	
	typedef struct{
		int r;
    int g;
    int b;
	}pixel;

	void randomizar (int x, int y, pixel **m){
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				m[i][j].r = rand() % 256;
				m[i][j].g = rand() % 256;
				m[i][j].b = rand() % 256;
			}
		}
	}

	void descolorir (int x, int y, pixel **m, pixel **mc){
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				mc[i][j].r = (0.3 * m[i][j].r);
				mc[i][j].g = (0.59 * m[i][j].g);
				mc[i][j].b = (0.11 * m[i][j].b);
			}
		}
	}

	void printar (int x, int y, pixel **m){
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				printf("%i",m[i][j].r);
				printf("%i",m[i][j].g);
				printf("%i\n",m[i][j].b);
			}
		}
	}

pixel **alocar(){
    pixel **m;
    m = (pixel **) malloc(10 * sizeof (pixel*));

    for(int i = 0; i < 10; i++){
        m[i] = (pixel *) malloc (15 * sizeof (pixel));
    }
    return m;
}

void liberar(pixel **m){
    for(int i = 0; i < 10; i++){
        free(m[i]);
    }

    free(m);
}
	
int main(void) {	
	pixel **rgb;
	pixel **gray;

  rgb = alocar();
  gray=alocar();

	randomizar(10,15,rgb);
	descolorir(10,15,rgb,gray);
	printar(10,15,gray);

  liberar(rgb);
  liberar(gray);
}