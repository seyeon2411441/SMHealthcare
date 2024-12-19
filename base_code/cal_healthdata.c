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

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
	//파일 쓰기 모드로 열기
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
    	//파일 열기 실패했을 때
        printf("There is no file for health data.\n");
        return;
    }

    // Exercise 정보 파일에 저장
    fprintf(file, "[Exercises]\n ");
    for (i=0;i<health_data->exercise_count;i++){
    	//운동의 이름과 칼로리 소모 파일에 출력
    	fprintf(file, "%s -%dkcal\n", health_data->exercises[i].exercise_name,health_data->exercises[i].calories_burned_per_minute);
	}
    
    
    //Diets 정보 파일에 저장
    fprintf(file, "\n[Diets] \n");
    for (i=0;i<health_data->diet_count;i++){
    	fprintf(file, "%s - %dKcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}



    // Total 정보 파일에 저장
    fprintf(file, "\n[Total] \n");
    
    //하루 권장 칼로리-총 섭취된칼로리+소모된 칼로리
    int remaining_calories=DAILY_CALORIE_GOAL - health_data->total_calories_intake + health_data -> total_calories_burned;
    //계산한 remaining calories 파일에 저장
	fprintf(file, "Remaining calories : %d kcal\n", remaining_calories);
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

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
  
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");


    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
 
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    
	 printf("=======================================================================\n");
}
