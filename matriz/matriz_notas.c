#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
	
	int i = 0, op;
	
    float *notas[10];  
    float *media[10];
    float *media_turma;
    
    
    media_turma=malloc(sizeof(float));
    
    do{
		printf("Deseja inserir a nota do %d aluno?\n", i+1);
    	printf("Sim(1);\nNao(2).\n");
    	scanf("%d", &op);
    	if(op==1){
    		printf("Adicione as notas:\n");
    		notas[i]=malloc(3*sizeof(float));
    		media[i]=malloc(sizeof(float));
    		
    		for(int j=0; j<3; j++){
    			printf("Digite a %d� nota: ", j+1);
    			scanf("%f", notas[i]+j);
    			*media[i]+=*(notas[i]+j);
			}
			i++;
    	}
    	if(op==2)
    	    break;
    	else
    		printf("Digite uma opcao valida!\n");
    		
	}while(op!=2);
	
    *media_turma=0.0;
    
	printf("Media dos alunos:\n");
	for(int j=0; j<i; j++){
		*media[j]=*(media[j])/3.0;
		printf("%d aluno: %.2f\n", j+1, *media[j]);
		*media_turma+=*media[j];
	}
	
	*media_turma=*media_turma/i;
	printf("Media da turma: %.2f\n", *media_turma);
	
	
    

    

	for(int j=0; j<i; j++){
	free(notas[j]);
    free(media[j]);
	}
    
    free(media_turma);

    return 0;
}


