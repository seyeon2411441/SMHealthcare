//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while () {
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    
     for(i=0;i<diet_list_size;i++)
	{
    	printf("%d. %s - %d \n", i+1,diet_list[i].food_name,diet_list[i].calories_intake);
	}
	while (1){
		printf("Choose the food number (0=exit):");
		scanf("%d",&choice);
		
		if (choice==0){
			printf("Exit.\n");
			break;
		}
		
		if(choice>0 && choice <= diet_list_size){
			if (health_data->diet_count<MAX_DIETS){
				health_data->diet[health_data->diet_count]=diet_list[choice-1];
				health_data->diet_count++;
				health_data->total_calories_intake+=diet_list[choice-1].calories_intake;
				
				printf("You intake %dkcal.\nTotal intake: %dkcal\n",diet_list[choice-1].calories_intake, health_data->total_calories_intake);
			}
			else{
				printf("You have reached the maximum calories.\n");
			}
		}else{
			printf("Wrong choice. Choose again.\n");
			continue;
		}
	}
}

