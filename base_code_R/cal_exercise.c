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

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }
    
    char line[100];//한줄 읽어올 버퍼
    while (fgets(line,sizeof(line),file)!=NULL) {//한 줄씩 읽음
    //(운동이름, 칼로리)를 성공적으로 읽었을때 운동정보를 exercise list에 저장, 사이즈 증가
    	if(sscanf(line, "%s %d",exercise_list[exercise_list_size].exercise_name,&exercise_list[exercise_list_size].calories_burned_per_minute)==2){
    		exercise_list_size++;
    		if (exercise_list_size>=MAX_EXERCISES){
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
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
	printf("The list of exercises: \n");
    for (i = 0; i < exercise_list_size; i++) {
        printf("%d. %s - %d calories per minute\n", i + 1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
    }
    


    // ToCode: to enter the exercise to be chosen with exit option
    // 유효한 식단 번호를 선택할 때까지 반복
    while (1){
	
		printf("Choose the exercise number (0 = exit):");
		scanf("%d", &choice);
		//선택이 0이면 종료됨
		if (choice==0){
			printf("Exit.\n");
			break;
		}else if (choice<1||choice>=exercise_list_size){
			printf("Wrong number. choose again.\n");
		}else{
			//유효한 숫자일 때
			printf("Enter the duration of exercise (in min): ");
	        scanf("%d",&duration);
	        	
				}
			
			//눙동 선택에 따른 소모 칼로리 계산
	        int total_burned_calories=duration*exercise_list[choice].calories_burned_per_minute;
	        // exercise_list[choice - 1]에 해당하는 운동 이름을 health_data의 exercises 배열에 복사
            // (exercise_count는 현재까지 기록된 운동의 개수이며, 그 위치에 이름을 저장)
        	strncpy(health_data->exercises[health_data->exercise_count].exercise_name,exercise_list[choice - 1].exercise_name,MAX_EXERCISE_NAME_LEN - 1);
        	// exercise_name의 마지막 자리에 null 문자를 넣어 문자열의 끝을 표시
            health_data->exercises[health_data->exercise_count].exercise_name[MAX_EXERCISE_NAME_LEN - 1] = '\0';
            // 선택한 운동의 분당 칼로리 소모량을 health_data에 기록
			health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice - 1].calories_burned_per_minute;
            // total_calories_burned에 소모된 칼로리를 누적해서 기록
			health_data->total_calories_burned +=total_burned_calories;
	        // 운동 기록을 추가한 후 exercise_count를 증가
			health_data->exercise_count++;
	        printf("You burned %d calories.\n", total_burned_calories);
	        
	        
        }
       
    }


		