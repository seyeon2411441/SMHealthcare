//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/
//건강 데이터를 파일에 저장하는 함수
//HEALTHFILEPATH 데이터를 저장할 파일 경로 
void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
	//쓰기모드로 파일 열기
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
    	//파일 열기 실패했을 경우
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for (i=0;i<health_data->exercise_count;i++){
    	//운동의 이름과 칼로리 소모 파일에 기록
    	fprintf(file, "%s -%dkcal\n", health_data->exercises[i].exercise_name,health_data->exercises[i].calories_burned_per_minute);
    	
	}
    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for (i=0;i<health_data->diet_count;i++){
    	//for 문으로 음식 이름과 칼로리 파일에 기록
    	fprintf(file, "%s - %dKcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    	//총 섭취 칼로리도 기록
    	fprintf(file, "Total calories intake- %dkcal\n", health_data->total_calories_intake);
    	fclose(file);
    }



    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    int remaining_calories = (health_data->total_calories_intake) - BASAL_METABOLIC_RATE - (health_data->total_calories_burned);
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calories - %d kcal\n", remaining_calories);
    
    fclose(file);
    
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/
//health 데이터 출력 함수 
void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for (i=0;i<health_data->exercise_count;i++){
		printf("Exercise: %s,Calories burned: %d kcal\n",health_data->exercises[i].exercise_name, health_data->exercises[i] .calories_burned_per_minute);
	}
  
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0;i<health_data->diet_count;i++){
    	printf("Food:%s, Calories intake: %dkcal\n",health_data->diet[i].food_name,health_data->diet[i].calories_intake);
	}


    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	int remaining_calories=health_data->total_calories_intake-BASAL_METABOLIC_RATE-health_data->total_calories_burned;
	printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);
	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
	printf("The remaining calories: %dkcal\n",remaining_calories);
 
 
    printf("=======================================================================\n \n");
    if (remaining_calories==0){
    	printf("You have consumed all your calories for today!");

	}
	//남은 칼로리<0 인경우
	else if (remaining_calories<0){
		printf("[Warning] Too few calories!");
		//섭취 칼로리가 일일 권장 칼로리에 도달한 경우
		if (health_data->total_calories_intake==DAILY_CALORIE_GOAL){
			printf("Your total calorie intake for Today has reached your goal!");
			//섭취 칼로리가 일일 권장 칼로리보다 적은 경우
		}else if (health_data->total_calories_intake<DAILY_CALORIE_GOAL){
			printf("Your total calorie intake for today has not reached your goal, remember to eat moare!!");
		//섭취 칼로리가 일일 권장 칼로리보다 많은 경우
		}else {
			printf("You have eaten more calories than planned today, but you have exercised too much!");
		}
		//남은 칼로리>0 인 경우
	}else{
		printf("Please exercise for your health!");
		//섭취 칼로리가 일일 권장 칼로리에 도달한 경우
		if (health_data->total_calories_intake==DAILY_CALORIE_GOAL){
			printf("Your total calorie intake for today has reached your goal!");
			//섭취 칼로리가 일일 권장 칼로리보다 적은 경우
		}else{
			printf("Your total calorie intake for today has not reached your goal, remember to eat more!!");
		}
	}
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    
	 printf("=======================================================================\n");
}
