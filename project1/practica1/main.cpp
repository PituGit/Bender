//Difinicions amb la variable d'activació de la llibreria gràfica, __viz_graphics__
#include "Definitions.h"


//Includes de les llibreries gràfiques
#ifdef GRAPHICS
	#define SDL_MAIN_HANDLED 
	#include "lib\libreria.h"
	#include <windows.h>
#endif 

#include <iostream>
#include <fstream>

//Mida del taulell
const int MIDATAULELL = 480;

//Numero de caselles i moviments
const int CASELLES = 8;
const int MOVIMENTS = 7;

//Funció per la lectura de la posició inicial del maó
void ReadInitialPosition(const std::string& filename, int *X, int *Y)
{
	std::ifstream file;
	file.open(filename.c_str()); //filename.c_str
	if (file.is_open())
	{
		file >> *X >> *Y;
		file.close();
	}
	else
	{
		std::cout << "error: file not found" << std::endl;
	}
}
//Funció per a guardar el fitxer de sortida amb els moviments
void WriteExitPath(const std::string& filename, int X[], int Y[], int lengthMov)
{
	std::ofstream fileOut;
	fileOut.open(filename.c_str());
	if (fileOut.is_open())
	{
		for (int i = 0; i < lengthMov; i++)
		{
			fileOut << X[i] << " " << Y[i] << std::endl;
		}
		fileOut.close();
	}
	else
	{
		std::cout << "error: file not found" << std::endl;
	}
}



int main(int argc, char* argv[])
{
	//Arxius per llegir i escriure per paràmetre
	if (argc == 3) 
	{

		#ifdef GRAPHICS
				SDL_SetMainReady();
				SDL_Init(SDL_INIT_VIDEO);

				// Declaració de l’objecte de la classe Game canviant el tamany per defecte de la pantalla
				Game joc(MIDATAULELL, MIDATAULELL);

				// Inicialització de l’entorn gràfic. S’ha de cridar abans de declarar o 
				// utilitzar qualsevol altre element de la llibreria
				joc.Init();

				// Inicialització de la variable “mao” amb el gràfic “mao.png” 
				Sprite mao;
				mao.Create("mao.png");
				// Inicialització de la variable “casella buida” amb el gràfic “cnegre.png” 
				Sprite cbuida;
				cbuida.Create("cnegre.png");
		#endif

		//Declaració variables per la posició del maó
		int posX = 0;
		int	posY = 0;
		ReadInitialPosition(argv[1], &posX, &posY); 
		//Inicialització del taulell
		int taulell[CASELLES][CASELLES];

		//Inicialització dels vectors per guardar el camí X,Y
		int pathX[MOVIMENTS];
		int pathY[MOVIMENTS];

		#if GRAPHICS
				//Pantalla gràfica
				joc.Video_ShowWindow();
				//Dibuixa el maó
				mao.Draw(posX * mao.getScaleY(), posY * mao.getScaleX()); //(columna/fila)

				//Actualització de la pantalla				
				joc.VideoUpdate();
				Sleep(500);
		#endif

		//guardem posició inicial
		pathX[0]=posX;
		pathY[0]=posY;
		
		//Bucle principal del joc
		do {
			#if GRAPHICS
						//Dibuix de la nova posició del maó i casella buida a l'anterior posició
						cbuida.Draw(posX * cbuida.getScaleX(), (posY)* cbuida.getScaleX());
						mao.Draw(posX * mao.getScaleX(), (posY + 1) * mao.getScaleX());

						joc.VideoUpdate();
						Sleep(500);
			#endif

			//Actualitza i guarda la nova posició 
			
			pathX[posY]=posX;
			pathY[posY]=posY;
			posY++;

		} while (posY <= MOVIMENTS-1);

		//Guardem els punts X,Y del camí seguit
		WriteExitPath(argv[2], pathX, pathY, MOVIMENTS); 

		#if GRAPHICS
				//Instruccio necesaria per poder finalitzar els gràfics
				SDL_Quit();
		#endif
	}
	return 0;
}
