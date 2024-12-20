//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

//메모리 오류가 떠서 조교님께 메일 드렸는데 새 폴더 저장 후 복붙하여 사용하는 것이 좋을 것 같다고 하셔서 업로드 주기가 최근인 점 양해 부탁드립니다!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	//health_data 0으로 초기ㅗ하
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    //운동, 식단, 건강데이터 목록 읽어오기
    //괄호 안 파일 경로
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);
    saveData(HEALTHFILEPATH,&health_data);
    //남은 칼로리 계산
    int remaining_calories=health_data.total_calories_intake-BASAL_METABOLIC_RATE-health_data.total_calories_burned;
    

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    //사용자가 종료할 때까지 반복
    do {
    	//남은 칼로리가 0일때
    	if (remaining_calories==0 ){
            printf("You have consumed all your calories for today! \n");
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	//1번 선택했을 경우. 함수불러오기
            	inputExercise(&health_data);
            	
                break;
                
            case 2:
            	//2번선택했을경우
            	inputDiet(&health_data);
            	
                break;
                
            case 3:
            	//3번
            	printHealthData(&health_data);
            	
                break;
                
            case 4:
            	//4번 Data 저장 후 종료 
            	saveData(HEALTHFILEPATH, &health_data);
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
            	//유효하지 않은옵션
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
        //남은 칼로리가 0보다 크고, 사용자가 종료하지 않았을 때 계속 반복
    } while (choice!=4 && remaining_calories>0);

    return 0;
}

