//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

//exercises.txt 에서 운동 목록 읽어오는 역할
void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (1 ) {
    	// 데이터 제대로 못읽으면 exercise_list_size 증가 시킴. 루프 계속됨
    	//읽은 값은 exercise_list 배열에 저장 
    	if (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute )!=2){
    		break;
		}
		if (exercise_list_size >= MAX_EXERCISES){
			break;
		}
		exercise_list_size++;
	}
	
	fclose(file);
}
/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/
//사용자가 운동 선택하고, 시간 입력하고, 소모된 칼로리 계산하는 함수
void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    for (i=0; i< exercise_list_size; i++){
    	printf("%d. %s - %d calories per minute\n",i+1,exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}                  
	//운동을 선택할 때까지 반복
	while (1){
		printf("Choose the exercise number (0 = exit):");
		scanf("%d", &choice);
		//선택이 0이면 종료됨
		if (choice==0){
			printf("Exit.\n");
			break;
		}
		//올바른 운동번호 일 때
		else if(choice>0 && choice <= exercise_list_size){
			printf("enter the duration of exercise(in min): ");
			scanf("%d", &duration);
			//토탈 칼로리 계산
			int total_calories_burned=exercise_list[choice-1].calories_burned_per_minute*duration;
			//운동 데이터 health_data 파일에 기록 
			int j;
			for (j = 0; j < MAX_EXERCISE_NAME_LEN - 1 && exercise_list[choice - 1].exercise_name[i] != '\0'; i++) {
                health_data->exercises[health_data->exercise_count].exercise_name[i] = exercise_list[choice - 1].exercise_name[i];
		    }
		    health_data->exercises[health_data->exercise_count].exercise_name[i] = '\0';
		    //칼로리 정보 작성
		    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice - 1].calories_burned_per_minute;
		    //지금까지 총 소모한 칼로리 갱신하기 
			health_data->total_calories_burned += total_calories_burned;
		    //운동 개수 카운트 
			health_data->exercise_count++;
			
		    printf("You burned %d calories.\n", total_calories_burned);
		    
		  // 입력된 운동 번호가 잘못되었을 때  
	}else{
		printf("Wrong choice. Choose again.\n");
	}
}
	




}