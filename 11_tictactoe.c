#include "main.h"
#include "st7735\st7735.h"

#define QUADRADO_0 matriz[0][0]
#define QUADRADO_1 matriz[0][1]
#define QUADRADO_2 matriz[0][2]
#define QUADRADO_3 matriz[1][0]
#define QUADRADO_4 matriz[1][1]
#define QUADRADO_5 matriz[1][2]
#define QUADRADO_6 matriz[2][0]
#define QUADRADO_7 matriz[2][1]
#define QUADRADO_8 matriz[2][2]
#define LIGA_LED1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LIGA_LED2 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LIGA_LED3 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LIGA_LED4 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)
#define DESLIGA_LED1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define DESLIGA_LED2 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define DESLIGA_LED3 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define DESLIGA_LED4 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)
#define BOTAO_ESQUERDO HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO_SELECT HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO_DIREITO HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)

void tabela (int XIX,int BOLINHA){ //se escreve os pontos no placar
if(XIX == 0){
	ST7735_WriteString(11,30,"0", Font_7x10, WHITE, BLACK);
}
else if(XIX == 1){
	ST7735_WriteString(11,30,"1", Font_7x10, WHITE, BLACK);
}
if(BOLINHA == 0){
    ST7735_WriteString(11,65,"0", Font_7x10, WHITE, BLACK);
}
else if(BOLINHA == 1){
    ST7735_WriteString(11,65,"1", Font_7x10, WHITE, BLACK);
}
return 0;
}


void ST7735_Test()
{
// escreve o placar (onde se marca as pontuações de "x" e "o")
	ST7735_WriteString(0,0,"34DS", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(9,10,"x", Font_11x18, WHITE, BLACK);
	ST7735_WriteString(9,45,"o", Font_11x18, WHITE, BLACK);
	ST7735_DrawLines();
}

void ST7735_DrawLines()
{

		//linha verticais
		ST7735_DrawLine(30, 5, 30, ST7735_HEIGHT-1, WHITE);

		ST7735_DrawLine(80, 0, 80, ST7735_HEIGHT-1, BLUE);
		ST7735_DrawLine(120, 0, 120, ST7735_HEIGHT-1, BLUE);
		HAL_Delay(0);

		//linhas horizontais
	    ST7735_DrawLine(40, 25, ST7735_WIDTH-1, 25, BLUE);
	    ST7735_DrawLine(40, 55, ST7735_WIDTH-1, 55, BLUE);
}





int main(void)
{
int matriz [3][3], XIX = 0, BOLINHA = 0, opcao = 0, cont = 0; // declarações iniciais
// matriz é a demarcação de onde podem ocorrer as jogadas, XIX e BOLINHA são os marcadores de pontuação
//opcao determina qual é o quadrado em que poderá ocorrer a demarcação de "x" ou "o" 
//e cont é a variavel que dita de quem é a jogada, lembrando que neste jogo é o "x" que inicia a rodada

while (1)
  {


      //INICIO JOGO (sendo uma melhor de 3)
      while (BOLINHA != 2 || XIX != 2){

        //LIMPANDO O JOGO/ ZERANDO A TABELA

    	  cont = 0, QUADRADO_0 = 0, QUADRADO_1 = 0,  QUADRADO_2 = 0, QUADRADO_3 = 0, QUADRADO_4 = 0, QUADRADO_5 = 0, QUADRADO_6 = 0, QUADRADO_7  = 0, QUADRADO_8 = 0;

    	  ST7735_FillScreen(BLACK); // reset 
    	  ST7735_Test();
    	  tabela(XIX, BOLINHA);

    	   int a = 1; // O a serve para reiniciar o jogo sem finalizar ele, em casos de empate e vitória não definitiva
    	   while (a == 1){

          //jogada XIX
           while (cont == 0){

        // mudança de opção
        	if (BOTAO_ESQUERDO == 0){
        		HAL_Delay(500);
        		opcao --;
        	}
        	if (BOTAO_DIREITO == 0){
        		HAL_Delay(500);
        		opcao ++;
        	}
        	if (opcao < 0){
        		opcao = 8;
        	}
        	if (opcao > 8){
        		opcao = 0;
        	}
        	
        	//verificação se o local esta marcado para a opção ser passada a diante (pular o quadrado marcado)
        	if ((QUADRADO_0 == 1 && opcao == 0)||(QUADRADO_1 == 1 && opcao == 1)||(QUADRADO_2 == 1 && opcao == 2)||(QUADRADO_3 == 1 && opcao == 3)||(QUADRADO_4 == 1 && opcao == 4)||(QUADRADO_5 == 1 && opcao == 5)||(QUADRADO_6 == 1 && opcao == 6)||(QUADRADO_7 == 1 && opcao == 7)||(QUADRADO_8 == 1 && opcao == 8)){
        	opcao ++;
        	}
        	else if ((QUADRADO_0 == 2 && opcao == 0)||(QUADRADO_1 == 2 && opcao == 1)||(QUADRADO_2 == 2 && opcao == 2)||(QUADRADO_3 == 2 && opcao == 3)||(QUADRADO_4 == 2 && opcao == 4)||(QUADRADO_5 == 2 && opcao == 5)||(QUADRADO_6 == 2 && opcao == 6)||(QUADRADO_7 == 2 && opcao == 7)||(QUADRADO_8 == 2 && opcao == 8)){
        	opcao ++;
        	}
        	
        	
        	if (QUADRADO_0 == 1){ //ver se está marcado por "x"
        		ST7735_WriteString(52,5,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_0 == 2){ //ver se está marcado por "o"
        		ST7735_WriteString(52,5,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 0){ //mostrar que pode ser marcado (indicado pela cor vermelha)
        		ST7735_WriteString(52,5,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 0){ //marcar
        		ST7735_WriteString(52,5,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_0 = 1;
        		opcao = 0;
        	} //caso nada seja verdade, não será mostrado nada!
        	else if ((QUADRADO_0 != 1)&&(QUADRADO_0 != 2)&&(opcao != 0)){
        		ST7735_WriteString(52,5," ", Font_11x18, WHITE, BLACK);
        	}
        	else{
        		ST7735_WriteString(52,5," ", Font_11x18, WHITE, BLACK);
        	}

        	if (QUADRADO_1 == 1){// mesma coisa que do quadrado 0 para o 1 e assim por diante até o 8
        		ST7735_WriteString(95,5,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_1 == 2){
        		ST7735_WriteString(95,5,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 1){
        		ST7735_WriteString(95,5,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 1){
        		ST7735_WriteString(95,5,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_1 = 1;
        		opcao = 0;
        	}
        	else{
        		ST7735_WriteString(95,5," ", Font_11x18, WHITE, BLACK);
        	}

        	if (QUADRADO_2 == 1){
        		ST7735_WriteString(135,5,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_2 == 2){
        		ST7735_WriteString(135,5,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 2){
        		ST7735_WriteString(135,5,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 2){
        		ST7735_WriteString(135,5,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_2 = 1;
        		opcao = 0;
        	}
        	else{
        		ST7735_WriteString(135,5," ", Font_11x18, WHITE, BLACK);
        	}

        	if (QUADRADO_3 == 1){
        		ST7735_WriteString(52,32,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_3 == 2){
        		ST7735_WriteString(52,32,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 3){
        		ST7735_WriteString(52,32,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 3){
        		ST7735_WriteString(52,32,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_3 = 1;
        		opcao = 0;
        	}
        	else{
        		ST7735_WriteString(52,32," ", Font_11x18, WHITE, BLACK);
        	}

        	if (QUADRADO_4 == 1){
        		ST7735_WriteString(95,32,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_4 == 2){
        		ST7735_WriteString(95,32,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 4){
        		ST7735_WriteString(95,32,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 4){
        		ST7735_WriteString(95,32,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_4 = 1;
        		opcao = 0;
        	}
        	else{
        		ST7735_WriteString(95,32," ", Font_11x18, WHITE, BLACK);
        	}


        	if (QUADRADO_5 == 1){
        		ST7735_WriteString(135,32,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_5 == 2){
        		ST7735_WriteString(135,32,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 5){
        		ST7735_WriteString(135,32,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 5){
        		ST7735_WriteString(135,32,"x", Font_11x18, WHITE, BLACK);
        		HAL_Delay(500);
        		cont ++;
        		QUADRADO_5 = 1;
        		opcao = 0;
        	}
        	else{
        		ST7735_WriteString(135,32," ", Font_11x18, WHITE, BLACK);
	        }



        	if (QUADRADO_6 == 1){
        	ST7735_WriteString(52,60,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_6 == 2){
        	ST7735_WriteString(52,60,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 6){
        	ST7735_WriteString(52,60,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 6){
        	ST7735_WriteString(52,60,"x", Font_11x18, WHITE, BLACK);
        	HAL_Delay(500);
        	cont ++;
        	QUADRADO_6 = 1;
        	opcao = 0;
        	}
        	else{
        	ST7735_WriteString(52,60," ", Font_11x18, WHITE, BLACK);
        	}


        	if (QUADRADO_7 == 1){
        	ST7735_WriteString(95,60,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_7 == 2){
        	ST7735_WriteString(95,60,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 7){
        	ST7735_WriteString(95,60,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 7){
        	ST7735_WriteString(95,60,"x", Font_11x18, WHITE, BLACK);
        	HAL_Delay(500);
        	cont ++;
        	QUADRADO_7 = 1;
        	opcao = 0;
        	}
        	else{
        	ST7735_WriteString(95,60," ", Font_11x18, WHITE, BLACK);
        	}

        	if (QUADRADO_8 == 1){
        	ST7735_WriteString(135,60,"x", Font_11x18, WHITE, BLACK);
        	}
        	else if (QUADRADO_8 == 2){
        	ST7735_WriteString(135,60,"o", Font_11x18, WHITE, BLACK);
        	}
        	else if(BOTAO_SELECT == 1 &&  opcao == 8){
        	ST7735_WriteString(135,60,"x", Font_11x18, RED, BLACK);
        	}
        	else if (BOTAO_SELECT == 0 && opcao == 8){
        	ST7735_WriteString(135,60,"x", Font_11x18, WHITE, BLACK);
        	HAL_Delay(500);
        	cont ++;
        	QUADRADO_8 = 1;
        	opcao = 0;
        	}else{
	        ST7735_WriteString(135,60," ", Font_11x18, WHITE, BLACK);
	        }
	        
	        
	    // verificação de vitória de "x"
        if (QUADRADO_0 == 1 && QUADRADO_1 == 1 && QUADRADO_2 == 1){ 
        	 XIX++;
        	 a++;
        	 cont = 2;
        }

        else if (QUADRADO_3 == 1 && QUADRADO_4 == 1 && QUADRADO_5 == 1){
        	 XIX++;
        	 a++;
        	 cont = 2;
        }
        else if (QUADRADO_6 == 1 && QUADRADO_7 == 1 && QUADRADO_8 == 1){
        	 XIX++;
        	 a++;
        	 cont = 2;
        }
        else if(QUADRADO_0 == 1 && QUADRADO_4 == 1 && QUADRADO_8 == 1){
        	 XIX++;
         	 a++;
         	 cont = 2;
                }
        else if (QUADRADO_2 == 1 && QUADRADO_4 == 1 && QUADRADO_6 == 1){
        	 XIX++;
        	 a++;
        	 cont = 2;
        }
        else if (QUADRADO_0 == 1 && QUADRADO_3 == 1 && QUADRADO_6 == 1){
            XIX++;
            a++;
            cont = 2;
                }
        else if (QUADRADO_1 == 1 && QUADRADO_4 == 1 && QUADRADO_7 == 1){
            XIX++;
            a++;
            cont = 2;
                        }
        else if (QUADRADO_2 == 1 && QUADRADO_5 == 1 && QUADRADO_8 == 1 ){
            XIX++;
            a++;
            cont = 2;
        // verificação de empate
                        }
        if(QUADRADO_0 != 0 && QUADRADO_1 != 0 && QUADRADO_2 != 0 && QUADRADO_3 != 0 && QUADRADO_4 != 0 && QUADRADO_5 != 0 && QUADRADO_6 != 0 && QUADRADO_7 != 0 && QUADRADO_8 != 0){
        	a++;
        	cont = 2;
          	  	  	    }
        }
        //jogada de BOLINHA
        //é a mesma coisa de "x", contanto para o outro jogador, o de "o" :O
        while (cont == 1){

        if (BOTAO_ESQUERDO == 0){
        HAL_Delay(500);
        opcao --;
        }
        if (BOTAO_DIREITO == 0){
        HAL_Delay(500);
        opcao ++;
        }
        if (opcao < 0){
        opcao = 8;
        }
        if (opcao > 8){
        opcao = 0;
        }

        if ((QUADRADO_0 == 1 && opcao == 0)||(QUADRADO_1 == 1 && opcao == 1)||(QUADRADO_2 == 1 && opcao == 2)||(QUADRADO_3 == 1 && opcao == 3)||(QUADRADO_4 == 1 && opcao == 4)||(QUADRADO_5 == 1 && opcao == 5)||(QUADRADO_6 == 1 && opcao == 6)||(QUADRADO_7 == 1 && opcao == 7)||(QUADRADO_8 == 1 && opcao == 8)){
        opcao ++;
        }
        else if ((QUADRADO_0 == 2 && opcao == 0)||(QUADRADO_1 == 2 && opcao == 1)||(QUADRADO_2 == 2 && opcao == 2)||(QUADRADO_3 == 2 && opcao == 3)||(QUADRADO_4 == 2 && opcao == 4)||(QUADRADO_5 == 2 && opcao == 5)||(QUADRADO_6 == 2 && opcao == 6)||(QUADRADO_7 == 2 && opcao == 7)||(QUADRADO_8 == 2 && opcao == 8)){
        opcao ++;
        }
    
        if (QUADRADO_0 == 2){
        ST7735_WriteString(52,5,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_0 == 1){
        ST7735_WriteString(52,5,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 0){
        ST7735_WriteString(52,5,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 0){
        ST7735_WriteString(52,5,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_0 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(52,5," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_1 == 2){
        ST7735_WriteString(95,5,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_1 == 1){
        ST7735_WriteString(95,5,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 1){
        ST7735_WriteString(95,5,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 1){
        ST7735_WriteString(95,5,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_1 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(95,5," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_2 == 2){
        ST7735_WriteString(135,5,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_2 == 1){
        ST7735_WriteString(135,5,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 2){
        ST7735_WriteString(135,5,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 2){
        ST7735_WriteString(135,5,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_2 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(135,5," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_3 == 2){
        ST7735_WriteString(52,32,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_3 == 1){
        ST7735_WriteString(52,32,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 3){
        ST7735_WriteString(52,32,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 3){
        ST7735_WriteString(52,32,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_3 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(52,32," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_4 == 2){
        ST7735_WriteString(95,32,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_4 == 1){
        ST7735_WriteString(95,32,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 4){
        ST7735_WriteString(95,32,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 4){
        ST7735_WriteString(95,32,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_4 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(95,32," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_5 == 2){
        ST7735_WriteString(135,32,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_5 == 1){
        ST7735_WriteString(135,32,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 5){
        ST7735_WriteString(135,32,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 5){
        ST7735_WriteString(135,32,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_5 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(135,32," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_6 == 2){
        ST7735_WriteString(52,60,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_6 == 1){
        ST7735_WriteString(52,60,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 6){
        ST7735_WriteString(52,60,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 6){
        ST7735_WriteString(52,60,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_6 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(52,60," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_7 == 2){
        ST7735_WriteString(95,60,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_7 == 1){
        ST7735_WriteString(95,60,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 7){
        ST7735_WriteString(95,60,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 7){
        ST7735_WriteString(95,60,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_7 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(95,60," ", Font_11x18, WHITE, BLACK);
        }

        if (QUADRADO_8 == 2){
        ST7735_WriteString(135,60,"o", Font_11x18, WHITE, BLACK);
        }
        else if (QUADRADO_8 == 1){
        ST7735_WriteString(135,60,"x", Font_11x18, WHITE, BLACK);
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 8){
        ST7735_WriteString(135,60,"o", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 8){
        ST7735_WriteString(135,60,"o", Font_11x18, WHITE, BLACK);
        HAL_Delay(500);
        cont --;
        QUADRADO_8 = 2;
        opcao = 0;
        }
        else{
        ST7735_WriteString(135,60," ", Font_11x18, WHITE, BLACK);
        }

        // verificação de vitória de "o"
        if (QUADRADO_0 == 2 && QUADRADO_1 == 2 && QUADRADO_2 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if (QUADRADO_3 == 2 && QUADRADO_4 == 2 && QUADRADO_5 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if (QUADRADO_6 == 2 && QUADRADO_7 == 2 && QUADRADO_8 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if(QUADRADO_0 == 2 && QUADRADO_4 == 2 && QUADRADO_8 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if (QUADRADO_2 == 2 && QUADRADO_4 == 2 && QUADRADO_6 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if (QUADRADO_0 == 2 && QUADRADO_3 == 2 && QUADRADO_6 == 2){
        BOLINHA++;
        a++;
        cont = 2;
        }
        else if (QUADRADO_1 == 2 && QUADRADO_4 == 2 && QUADRADO_7 == 2){
        BOLINHA++;
        a++;
    	cont = 2;
        }
        else if (QUADRADO_2 == 2 && QUADRADO_5 == 2 && QUADRADO_8 == 2 ){
      	BOLINHA++;
        a++;
        cont = 2;
        }
        if(QUADRADO_0 != 0 && QUADRADO_1 != 0 && QUADRADO_2 != 0 && QUADRADO_3 != 0 && QUADRADO_4 != 0 && QUADRADO_5 != 0 && QUADRADO_6 != 0 && QUADRADO_7 != 0 && QUADRADO_8 != 0){
       	a++;
      	cont = 2;
         }
       }
     }
    if (XIX>1||BOLINHA>1){ //telas de vitórias 
    	if (XIX > 1){ //tela vitória de "x" (ou xix)
    	ST7735_FillScreen(WHITE_BLUE);
    	ST7735_WriteString(52,5,"VITORIA", Font_11x18, BLACK, WHITE_BLUE);
    	ST7735_WriteString(75,32,"DE", Font_11x18, BLACK, WHITE_BLUE);
    	ST7735_WriteString(77,55,"X", Font_16x26, BLACK, WHITE_BLUE);

    	}
    	if (BOLINHA > 1){ //tela vitória de "o" (ou bolinha)
    	ST7735_FillScreen(RED);
    	ST7735_WriteString(52,5,"VITORIA", Font_11x18, BLACK, RED);
    	ST7735_WriteString(75,32,"DE", Font_11x18, BLACK, RED);
    	ST7735_WriteString(77,55,"o", Font_16x26, BLACK, RED);

        }
    	  for(int pisca=0;pisca<3;pisca++){ //comemoração de vitória muito legal :)
    	  LIGA_LED1;
    	  LIGA_LED2;
    	  LIGA_LED3;
    	  LIGA_LED4;
    	  HAL_Delay(200);
    	  DESLIGA_LED1;
    	  DESLIGA_LED2;
    	  DESLIGA_LED3;
    	  DESLIGA_LED4;
    	  HAL_Delay(200);
    	  LIGA_LED4;
    	  HAL_Delay(200);
    	  DESLIGA_LED4;
    	  LIGA_LED3;
    	  HAL_Delay(200);
    	  DESLIGA_LED3;
    	  LIGA_LED2;
    	  HAL_Delay(200);
    	  DESLIGA_LED2;
    	  LIGA_LED1;
    	  HAL_Delay(200);
    	  DESLIGA_LED1;
    	  HAL_Delay(300);
    	  }
    	XIX = 0, BOLINHA = 0; //zera as pontuações de "x" e "o"
    	}
      }
    }