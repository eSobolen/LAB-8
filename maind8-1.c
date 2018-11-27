#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_MOD 0

#define MAX_CARS 10
#define STR_LEN 255
#define FREE_CAR_SLOT -1

#define CAR_REGNUMBER 		0
#define CAR_MODEL 			1
#define CAR_RUN 			2
#define CAR_WORKER_NAME 	3
#define CAR_PRICE 			4



/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct car_type
{
	int 	carRegNumber;
	char 	carModel[STR_LEN];		
	int 	carRun;
	char 	workerName[STR_LEN];
	int 	price;
} carServise[MAX_CARS];

void printAllCars();
void printAllCarsFrom(struct car_type cars[]);
void EditCarsAttribute(int AttributeN,char satr[], struct car_type *car);
void clearCarServ();
void clearCarIn(struct car_type cars[]);
void log_testInfo(char info[]);
void deleteCar(struct car_type *car);
void log_testInfo(char info[]);
void sortingAllCars();

int main(int argc, char *argv[]) 
{
	int regNum, carRun, price, atr, exit, exitCount, index;
	char carModel[STR_LEN], workerName[STR_LEN], str[STR_LEN];
	struct car_type buffer[MAX_CARS];
	char action = 0; 
	
	fflush(stdin);
	
	clearCarServ();
	createCar(123,"tt",343445,"Tom",400);
	createCar(453,"Ford",695443,"Nik",900);
	createCar(767,"Lada",654323,"Tom",900);
	createCar(443,"Uaz",343434,"Nik",1200);
	createCar(953,"Uaz-23",123523,"Nik",1600);
	createCar(153,"isuzu",977434,"John",200);
//	deleteCar(&carServise[2]);
	clearCarIn(buffer);
	
	printAllCars();
	//printCar(carServise[0]);

	while(exit != 0)
	{
		if(exitCount > 1000)
		{
			exit = 0;
		}
		
		strcpy(str,"");
		index = 0;
		clearCarIn(buffer); 
		
		printf("1 - Enter car\n");
		printf("2 - Sorting cars\n");
		printf("3 - Search car\n");
		printf("4 - Edit car\n");
		printf("5 - Delet car\n");
		printf("6 - Print cars\n");
		printf("7 - exit\n");
		action = getch();
		switch(action)
		{
			case '1':
				printf("Enter car regNum, car model, car run, worker name and price\n");	
				scanf("%d%s%d%s%d",&regNum,&carModel,&carRun,&workerName,&price);
				if(createCar(regNum,carModel,carRun,workerName,price))
				{
					printf("cant create car, garage is full\n");
				}
			break;
			case '2':
				sortingAllCars();
			break;
			case '3':
				printf("Search by\n");
				printf("1 - regNum\n");
				printf("2 - car model\n");
				printf("3 - car run\n");
				printf("4 - worker name\n");
				printf("5 - price\n");
				action = getch();
				switch(action)
				{
					case '1':
						atr = CAR_REGNUMBER;
					break;
					case '2':
						atr = CAR_MODEL;
					break;
					case '3':
						atr = CAR_RUN;
					break;
					case '4':
						atr = CAR_WORKER_NAME;
					break;
					case '5':
						atr = CAR_PRICE;
					break;
					default:
						printf("not correct atribute\n");
						printf("Search by regNum\n");
						atr = CAR_REGNUMBER;
					break;
				}
				printf("Enter element\n");
				fflush(stdin);
				gets(str);
				findCarsByAttribute(atr, str, buffer);
				printf("Cars whith elsement %s:\n",str);
				printAllCarsFrom(buffer);
			break;
			case '4':
				printf("Enter Index\n");
				scanf("%d",&index);
				if(carNum2Index(&index) == -1)
				{
					printf("not correct index\n");
					break;
				}
				printf("Edit:\n");
				printf("1 - regNum\n");
				printf("2 - car model\n");
				printf("3 - car run\n");
				printf("4 - worker name\n");
				printf("5 - price\n");
				action = getch();
				switch(action)
				{
					case '1':
						atr = CAR_REGNUMBER;
					break;
					case '2':
						atr = CAR_MODEL;
					break;
					case '3':
						atr = CAR_RUN;
					break;
					case '4':
						atr = CAR_WORKER_NAME;
					break;
					case '5':
						atr = CAR_PRICE;
					break;
					default:
						printf("not correct atribute\n");
						printf("Search by regNum\n");
						atr = CAR_REGNUMBER;
					break;
				}
				printf("Enter element\n");
				fflush(stdin);
				gets(str);
				EditCarsAttribute(atr,str,&carServise[index]);
			break;
			case '5':
				printf("Enter Index\n");
				scanf("%d",&index);
				if(carNum2Index(&index) == -1)
				{
					printf("not correct index\n");
					break;
				}
				printf("Delet car whith index = %d\n",index);
				deleteCar(&carServise[index]);
			break;
			case '6':
				printf("Now we have this cars:\n");
				printAllCars();
			break;
			case '7':
				return 0;
			break;
			default:
				exitCount++;
				printf("not correct action\n");
			break;
		}
		printf("\n");
	}
	return 0;
}

int findFreeCarSlot()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		if(carServise[i].carRegNumber == FREE_CAR_SLOT)
		{
			return i;	
		}
	}
	return -1;
}

int carNum2Index(int *num)
{
	int i;
	if(*num < 0 || *num >= MAX_CARS)
	{
		return -1;
	}
	for(i = 0; i < MAX_CARS; i++)
	{
	//	printf("%d",*num);
		log_testInfo("Num");
		if(carServise[i].carRegNumber != FREE_CAR_SLOT)
		{
			*num = *num - 1;	
			
			log_testInfo("Num--");
		}
		if(*num <= 0)
		{
			*num = i;
			log_testInfo("FindNum");
			return i;
		}
	}
	//printf("We dont have a car whith this index");
	return -1;
}

void EditCarsAttribute(int AttributeN,char satr[], struct car_type *car)
{
	int iatr = -1;
	int i ,j = 0;
	iatr = atoi(satr);	
	log_testInfo(satr);
	log_testInfo("start Edit car");
	switch(AttributeN)
	{
		case CAR_REGNUMBER:	
			//log_testInfo("CAR_REGNUMBER");
			car->carRegNumber = iatr;
		break;
		case CAR_MODEL:	
			//log_testInfo("CAR_MODEL");
			strcpy(car->carModel, satr);
		break;
		case CAR_RUN:
			//log_testInfo("CAR_RUN");	
			car->carRun= iatr;	
		break;
		case CAR_WORKER_NAME:	
			//log_testInfo("CAR_WORKER_NAME");
			//log_testInfo(satr);
		//	log_testInfo(carServise[i].workerName);
			strcpy(car->workerName, satr);
		break;
		case CAR_PRICE:
			//log_testInfo("CAR_PRICE");
			car->price = iatr;
		break;
	}
}

int findCarsByAttribute(int AttributeN,char satr[], struct car_type find[])
{
	int iatr = -1;
	int i ,j = 0;
	iatr = atoi(satr);	
	log_testInfo(satr);
	log_testInfo("start Finding car");
	for(i = 0; i < MAX_CARS; i++)
	{
		switch(AttributeN)
		{
			case CAR_REGNUMBER:	
				//log_testInfo("CAR_REGNUMBER");
				iatr = atoi(satr);
				if(carServise[i].carRegNumber == iatr)
				{
					find[j] = carServise[i];
					j++;	
				}	
			break;
			case CAR_MODEL:	
				//log_testInfo("CAR_MODEL");
				if(strncmp(satr, carServise[i].carModel, STR_LEN) == 0)
				{
					find[j] = carServise[i];	
					j++;
				}	
			break;
			case CAR_RUN:
				//log_testInfo("CAR_RUN");	
				if(carServise[i].carRun == iatr)
				{
					find[j] = carServise[i];
					j++;
				}	
			break;
			case CAR_WORKER_NAME:	
				//log_testInfo("CAR_WORKER_NAME");
				//log_testInfo(satr);
			//	log_testInfo(carServise[i].workerName);
				if(strncmp(satr, carServise[i].workerName, STR_LEN) == 0)
				{
					log_testInfo("We find car CAR_WORKER_NAME");
					find[j] = carServise[i];	
					j++;
				}
			break;
			case CAR_PRICE:
				//log_testInfo("CAR_PRICE");
				iatr = atoi(satr);	
				if(carServise[i].price == iatr)
				{
					find[j] = carServise[i];	
					j++;
				}	
			break;
		}
	}
	return j;	
}

void sortingAllCars()
{
	int i, j;
	struct car_type tmp;
	for(i = 0 ; i < MAX_CARS - 1; i++) 
	{ 
		for(j = 0 ; j < MAX_CARS - i - 1 ; j++) 
		{  
			if(carServise[j].carRegNumber > carServise[j+1].carRegNumber) 
			{           
				tmp = carServise[j+1];
				carServise[j+1] = carServise[j];
				carServise[j] = tmp; 
			}
		}
    }
}

void printCar(struct car_type* car)
{
	printf("%d\t%s\t%d\t%s\t%d\n",car->carRegNumber, car->carModel, car->carRun, car->workerName, car->price);
}

void printAllCars()
{
	printAllCarsFrom(carServise);
}

void printAllCarsFrom(struct car_type cars[])
{
	int i;
	printf("\n");
	for(i = 0; i < MAX_CARS; i++)
	{
		if(cars[i].carRegNumber != FREE_CAR_SLOT || TEST_MOD)
		{
			printCar(&cars[i]);
		}
	}
	printf("\n");
}

int createCar(int carRegNumber,char carModel[],int carRun,char workerName[],int price)
{
	struct car_type *carServ;
	int indx = findFreeCarSlot();
	if(indx == -1)
	{
		log_testInfo("ERROR: createCar - cant find free car slot\n");
		return 1;
	}
	
	carServise[indx].carRegNumber = carRegNumber;
	strcpy(carServise[indx].carModel,carModel);
	carServise[indx].carRun = carRun;
	strcpy(carServise[indx].workerName,workerName);
	carServise[indx].price = price;
	return 0;
}

void clearCarServ()
{
	clearCarIn(carServise);
}

void clearCarIn(struct car_type cars[])
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		deleteCar(&cars[i]);
	}
}

void deleteCar(struct car_type *car)
{	
	car->carRegNumber = FREE_CAR_SLOT;
	strcpy(car->carModel,"not a car");
	car->carRun = 0;
	strcpy(car->workerName,"do not have a worker");
	car->price = 0;
}

void log_testInfo(char info[])
{
	if(TEST_MOD)
	{
		puts(info);
	}
}
