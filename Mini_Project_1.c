/*
 ============================================================================
 Name          : Mini_Project_1.c
 Author        : Naiera Seifeldin
 Project title : Vehicle Control Project
 Description   : Implemented using structures, enumerations, if statements,
 switch statements, functions passed by address, pointers.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ======================= Structure ==================================*/
struct Vehicle_states {
	char colour;
	int Speed , room_temp , engine_temp , engine_state , AC_state;
	int engine_temp_control_state;
}Vehicle; // Vehicle is our car which has all these members (states)


/* =======================Initializations=============================*/

// if = 1 then will run whole code without removing the lines between
// #if #endif ,, if = 0 then will run code without those lines
#define WITH_ENGINE_TEMP_CONTROLLER 1  /* For Requirement_9 : BONUS PART */

enum {
	Engine_OFF , Engine_ON  // Engine states off=0 , on=1
};

enum {
	AC_OFF , AC_ON      // AC states off=0 , on=1
};

enum {
	Controller_OFF , Controller_ON // Engine temperature controller states
};


/* =====================Function prototypes============================*/
// type void since no return but structure is passed as argument and accessed by pointers
void Sensor_Menu( struct Vehicle_states * Vehicle );
void EngineOff_Menu( struct Vehicle_states * Vehicle );
void Calculate_Speed( struct Vehicle_states * Vehicle );
void Set_Room_Temp( struct Vehicle_states * Vehicle );
void Set_Engine_Temp( struct Vehicle_states * Vehicle );
void Control_AC ( struct Vehicle_states * Vehicle );
void Display_current_vehicle_state( struct Vehicle_states * Vehicle );


/* ===================================================================*/

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* initialize values */
	Vehicle.engine_state=Engine_OFF;
	Vehicle.colour='G';
	Vehicle.Speed=0;
	Vehicle.room_temp= 30;
	Vehicle.AC_state=AC_OFF;

#if( WITH_ENGINE_TEMP_CONTROLLER == 1 )
	  Vehicle.engine_temp=100;
	  Vehicle.engine_temp_control_state=Controller_OFF;
#endif

	char screen_menu;

	/* Main Menu */
	printf("Choose your required option: \n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	scanf(" %c",&screen_menu);

	switch(screen_menu)
	{
	/* Requirement_2 */
	case'c': // empty case so both will have same output
	case 'C': //for if user enter capital letter
		printf("Quit the system\n\n");
		break;

	/* Requirement_3 */
	case'b':
	case'B':
		EngineOff_Menu( &Vehicle );
		break;
	/* Requirement_5 */
	case'a':
	case'A':
		Sensor_Menu( &Vehicle );
		break;

	default:
		printf("Wrong input!\n");

	}
   return 0;
}


/* ================ Are you Sure you want to turn off? ================*/

void EngineOff_Menu(struct Vehicle_states * Vehicle)
{
	char engineoff_menu;

	    printf("Choose again your required option: \n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c",&engineoff_menu);

		switch(engineoff_menu)
		{
		case'c':
		case 'C':
				printf("Quit the system\n\n");
				break;

		case'b':
		case'B':
			Vehicle->engine_state=Engine_OFF;
			    printf("Engine is OFF\n\n");
				break;

		case'a':
		case'A':
			Vehicle->engine_state=Engine_ON;
			    printf("Engine is ON\n\n");
				Sensor_Menu( Vehicle );
				break;
		}
}


/* ======================= Sensor Menu ================================*/

void Sensor_Menu( struct Vehicle_states * Vehicle )
{
	Display_current_vehicle_state( Vehicle ); /* For Requirement_6 */
	char sensor_menu;
	      printf("Choose your required option: \n");
	      printf("a. Turn off the engine\n");
	      printf("b. Set the traffic light color\n");
	      printf("c. Set the room temperature\n");

#if( WITH_ENGINE_TEMP_CONTROLLER == 1 ) /* Requirement_9-5-d */
	      printf("d. Set the engine temperature\n");
#endif

	      scanf(" %c",&sensor_menu);

	      switch(sensor_menu)
	      {
	      case'a':
	      case'A':
	      {
	    	  EngineOff_Menu( Vehicle );
	      }
	    	  break;

	      case'b':
	      case'B':
	      {
	    	  printf("Enter required colour:");
	    	  scanf(" %c" , &(Vehicle->colour));
	    	  printf("\n");
	    	  Calculate_Speed( Vehicle );
	    	  Sensor_Menu( Vehicle ); /* For Requirement_6 */
	    	  break;
	      }

	      case'c':
	      case 'C':
	      {
	    	  printf("Enter required room temperature:");
	    	  scanf("%d",&(Vehicle->room_temp));
	    	  printf("\n");
	    	  Set_Room_Temp( Vehicle);
	    	  Sensor_Menu( Vehicle ); /* For Requirement_6 */
	    	  break;
	      }
#if( WITH_ENGINE_TEMP_CONTROLLER == 1 )  /* Requirement_9-7-c */
	      case'd':
	      case 'D':
	      {
	    	  printf("Enter required engine temperature:");
	    	  scanf("%d",&(Vehicle->engine_temp));
	    	  printf("\n");
	    	  Set_Engine_Temp( Vehicle);
	    	  Sensor_Menu( Vehicle ); /* For Requirement_6 */
	    	  break;
	      }
#endif

	      default:
	      {
	    	  printf("Wrong input!\n");
	    	  Sensor_Menu( Vehicle ); /* For Requirement_6 */
	      }
	}
}


/* ======== Calculate Speed of car depend on traffic colour ==========*/

void Calculate_Speed( struct Vehicle_states * Vehicle ) /* Requirement_7-a */
{
	    switch (Vehicle->colour)
	    {
	    case'g':
	    case'G':
	    	Vehicle->Speed=100;
	    	break;

	    case'o':
	    case'O':
	    	Vehicle->Speed=30;
	    	break;

	    case'r':
	    case'R':
	    	Vehicle->Speed=0;
	    	break;
	}
}


/* ====================== Set Room Temperature ========================*/

void Set_Room_Temp(struct Vehicle_states * Vehicle)  /* Requirement_7-b */
{
	if ((Vehicle->room_temp) <10)
	{
		Vehicle->AC_state=AC_ON;
		Vehicle->room_temp=20;
	}
	else if((Vehicle->room_temp) >30)
	{
		Vehicle->AC_state=AC_ON;
		Vehicle->room_temp=20;
	}
	else
	{
		Vehicle->AC_state=AC_OFF;
	}
}


/* ===================== Set Engine Temperature =======================*/

void Set_Engine_Temp(struct Vehicle_states * Vehicle) /* Requirement_7-c */
{
	if ((Vehicle->engine_temp) < 100)
	{
		Vehicle->engine_temp_control_state=Controller_ON;
		Vehicle->engine_temp=125;
	}
	else if((Vehicle->engine_temp) > 150)
	{
		Vehicle->engine_temp_control_state=Controller_ON;
		Vehicle->engine_temp=125;
	}
	else
	{
		Vehicle->engine_temp_control_state=Controller_OFF;
	}
}


/* ===================== Control AC depend on speed ===================*/

void Control_AC (struct Vehicle_states * Vehicle) /* Requirement_7-d */
{
	if (Vehicle->AC_state==AC_OFF)
	{
		Vehicle->AC_state=AC_ON;
	}
	Vehicle->room_temp= ((Vehicle->room_temp * 5) / 4) + 1;

#if( WITH_ENGINE_TEMP_CONTROLLER == 1 ) /* Requirement_9-7-d-ii */
	if (Vehicle->engine_temp_control_state==Controller_OFF)
	{
		Vehicle->engine_temp_control_state=Controller_ON;
	}
	Vehicle->engine_temp= ((Vehicle->engine_temp * 5) / 4) + 1;
#endif
}


/* ===================== Print all current states ====================*/

void Display_current_vehicle_state( struct Vehicle_states * Vehicle ) /* Requirement_7-e */
{
	if(30==(Vehicle->Speed))
	{
		Control_AC(Vehicle);
	}
	if (Vehicle->engine_state==Engine_OFF)
	{
		printf("Engine state: OFF\n");
	}
	else
	{
		printf("Engine state: ON\n ");
	}

	if (Vehicle->AC_state==AC_OFF)
	{
		printf("AC state: OFF\n");
	}
	else
	{
		printf("AC state: ON\n ");
	}

	printf("Vehicle speed: %d Km/Hr\n" , Vehicle->Speed);
	printf("Room Temperature: %d C\n" , Vehicle->room_temp);

#if( WITH_ENGINE_TEMP_CONTROLLER == 1 ) /* Requirement_9-7-e-v-vi */
	if (Vehicle->engine_temp_control_state==Controller_OFF)
	{
		printf("Engine Temperature Controller State: OFF\n");
	}
	else
	{
		printf("Engine Temperature Controller State: ON\n ");
	}

	printf("Engine Temperature: %d C\n\n" , Vehicle->engine_temp);
#endif
}


/* ===================================================================*/
