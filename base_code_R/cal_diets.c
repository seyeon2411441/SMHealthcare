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
     
    char line[100];//한줄 읽어올 버퍼
    while (fgets(line,sizeof(line),file)!=NULL) {//한 줄씩 읽음
    //(운동이름, 칼로리)를 성공적으로 읽었을때 운동정보를 exercise list에 저장, 사이즈 증가
    	if(sscanf(line, "%s %d",exercise_list[exercise_size].exercise_name,&exercise_list[exercise_size].calories_burned_per_minute)minute)==2){
    		exercise_list_size++;
    		if (exercise_size>=MAX_EXERCISES){
    			break;
			}
		}else{
			//잘못된 형식이 있을 경우
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

//식단 선택, 섭취한 칼로리 기록

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    //diet list size 만큼 반복하여 식사 목록 출력
     for(i=0;i<diet_list_size;i++)
	{
    	printf("%d. %s - %d \n", i+1,diet_list[i].food_name,diet_list[i].calories_intake);
	}
	while (1){
		//무한루프
		printf("Choose the food number (0=exit):");
		scanf("%d",&choice);
		
		if (choice==0){
			printf("Exit.\n");
			break;
		}
		//유효 숫자일 때
		if(choice>0 && choice <= diet_list_size){
			//최대 식사 수를 초과하지 않았을때 
			if (health_data->diet_count<MAX_DIETS){
				//해당 식사를 health data에 저장, diet count 증가, 해당 음식의 칼로리를total_calories_intake에 더함
				health_data->diet[health_data->diet_count]=diet_list[choice-1];
				health_data->diet_count++;
				health_data->total_calories_intake+=diet_list[choice-1].calories_intake;
				
				printf("You intake %dkcal.\nTotal intake: %dkcal\n",diet_list[choice-1].calories_intake, health_data->total_calories_intake);
			}
			//MAX DIETS 양 이상
			else{
				printf("You have reached the maximum calories.\n");
			}
			//유효하지 않은 숫자 선택시
		}else{
			printf("Wrong choice. Choose again.\n");
			continue;
		}
	}
}

