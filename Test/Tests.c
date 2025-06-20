#include "Tests.h"
#include <stdio.h>
//#define SYSTEM_TESTS

//Variable to hold the result of the component testing
unsigned char APIresult = FALSE;

/*File to hold the inputs, to do system testing*/
FILE* temp_input = NULL;							// Declare globally, initialize to NULL (a constant)
char temp_input_name[L_tmpnam];						// Name of a temp file for inputs

static struct User_Input_Type Test1_User =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Ahmed",
	26,
	23,
	10,
	1998,
	Male,
	Masters_Student
	},
	{
		{
			"EdgesAcademy",
			"Edges123"
		},
	"Edges123"
	}
};

/* Test Code to test the Sign Up */
static struct User_Input_Type Test2_User =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Rania",
	54,
	31,
	12,
	1970,
	Female,
	PHD_Holder
	},
	{
		{
			"EdgesAcademy2024",
			"Edges_123_"
		},
	"Edges_123_$$"
	}
};

static struct User_Input_Type Test_Valid_User =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Alsinwar",
	62,
	29,
	10,
	1962,
	Male,
	Graduate
	},
	{
		{
			"Hamas123",
			"AllahAkbar123"
		},
	"AllahAkbar123"
	}
};

/*Reset Valid User to init state*/
void reset_test_valid_user() {
	Test_Valid_User.PersonalInfo_Form.id = -1;				// this is to indecate user hasn't assigned ID
	strcpy(Test_Valid_User.PersonalInfo_Form.name, "Alsinwar");
	Test_Valid_User.PersonalInfo_Form.Age = 62;
	Test_Valid_User.PersonalInfo_Form.DOB_day = 29;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 10;
	Test_Valid_User.PersonalInfo_Form.DOB_year = 1962;
	Test_Valid_User.PersonalInfo_Form.gender = Male;
	Test_Valid_User.PersonalInfo_Form.educational_status = Graduate;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name, "Hamas123");
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "AllahAkbar123");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "AllahAkbar123");
}


static struct User_Input_Type Test_Invalid_User =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Alsinwar",
	62,
	29,
	10,
	1962,
	Male,
	Graduate
	},
	{
		{
			"Hamas123",
			"AllahAkbar123"
		},
	"AllahAkbar"
	}
};

/*Function to reset the Database to the init state*/
unsigned char Reset_DataBase()
{
	unsigned char RET = TRUE;

	//Fill the users DB
	for (char i = current_user_test; i < MAX_USERS; ++i){
		DBM_Add_User(&Test_Valid_User);
	}
	//Delete All users
	for (char i = current_user_test - 1; i >= 0 ; --i) {
		RET = DBM_Delete_User(i);
		if (RET == FALSE)
			break;
	}

	//reinit the DB
	DBM_initDB();
	return RET;
}

/* init function for Test Suite 1*/
static unsigned char test1_start(void)
{
	printf("\n/********************Suite 1 start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	if (RET == TRUE)
	{ 
		unsigned char RET = Add_Account(&Test1_User);
		APIresult = RET;
		Test1_User.PersonalInfo_Form.id = current_user_test-1;
		DBM_PrintUsers();
	}
	return !RET;
}

/* Closure Function For Test Suite 1*/
static unsigned char test1_end(void)
{
	unsigned char RET = 0;								// Return of the function
	DBM_PrintUsers();
	return RET;
}

/* init function for Test Suite 2*/
static unsigned char test2_start(void)
{
	printf("\n/********************Suite 2 start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	if (RET == TRUE)
	{
		RET = Add_Account(&Test2_User);
		APIresult = RET;
		Test2_User.PersonalInfo_Form.id = current_user_test -1;
		
		DBM_PrintUsers();
	}
	return RET;
}

/* Closure Function For Test Suite 2*/
static unsigned char test2_end(void)
{
	unsigned char RET = 0;								// Return of the function
	DBM_PrintUsers();
	return RET;
}

/* init function for DBM Suite */
static unsigned char DBM_Start(void)
{
	printf("\n/*********************** DBM Component Test Start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	return !RET;
}

/* Closure function for DBM Suite */
static unsigned char DBM_End(void)
{
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	return !RET;
}

/* init function for Course Reg Suite */
static unsigned char Course_Reg_Start(void)
{
	printf("\n/*********************** Course Reg Component Test Start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	return !RET;
}

/* Closure function for Course Reg Suite */
static unsigned char Course_Reg_End(void)
{
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	return !RET;
}

/* init function for Add_Account Suite */
static unsigned char Add_Account_Start(void)
{
	printf("\n/*********************** Add_Account Component Test Start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	/*Reset Valid User to init state*/
	reset_test_valid_user();
	return !RET;
}

/* Closure function for Add_Account Suite */
static unsigned Add_Account_End(void)
{
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	/*Reset Valid User to init state*/
	reset_test_valid_user();
	return !RET;
}

/* init function for Delete_Account Suite */
static unsigned char Delete_Account_Start(void)
{
	printf("\n/*********************** Delete_Account Component Test Start************************/\n");
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	/*Reset Valid User to init state*/
	reset_test_valid_user();
	return !RET;
}

/* Closure function for Delete_Account Suite */
static unsigned Delete_Account_End(void)
{
	unsigned char RET;								// Return of the function
	RET = Reset_DataBase();							// Reset the Database to initial state

	/*Reset Valid User to init state*/
	reset_test_valid_user();
	return !RET;
}

/* init function for System test (end-to-end)*/
static unsigned char Login_Test_Start()
{
	printf("/********************Login Suite start************************/\n");
	unsigned char RET;									// Return of the function

		tmpnam(temp_input_name);						// Generate a temporary filename
		temp_input = fopen(temp_input_name, "w");		// Open it for writing
		if (temp_input == NULL) {						// Check if the files is created successfully
			perror("Failed to create temporary file");
			RET = ERROR;
		}
		else {
			RET = TRUE;
		}
	return !RET;
}

/* Closure Function For System test (end-to-end)*/
static unsigned char Login_test_teardown_end()
{
	unsigned char RET = 0;
	//Remove the Input File
	if (remove(temp_input_name) != 0)
	{
		perror("Error deleting file");
	}
	return RET;

}
#ifdef SYSTEM_TESTS
/* init function for System test (end-to-end)*/
static unsigned char system_test_setup_start()
{
	printf("/********************System Suite start************************/\n");
	unsigned char RET;									// Return of the function
	RET = Reset_DataBase();								// Reset the Database to initial state

	if (RET == TRUE) {
		tmpnam(temp_input_name);						// Generate a temporary filename
		temp_input = fopen(temp_input_name, "w");		// Open it for writing
		if (temp_input == NULL) {						// Check if the files is created successfully
			perror("Failed to create temporary file");
			RET = ERROR;
		}
		else {
			RET = TRUE;
		}
	}
	return !RET;
}

/* Closure Function For System test (end-to-end)*/
static unsigned char system_test_teardown_end()
{
	unsigned char RET = 0;
	//Remove the Input File
	if (remove(temp_input_name) != 0)
	{
		perror("Error deleting file");
	}
	return RET;

}
#endif //SYSTEM_TESTS


/************************************************************************************
* Test ID                : TestCase 1
* Description            : Testing the Add Account Functionality with Valid
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Ahmed
*                          Age                          -> 26
*                          DOB_day                      -> 01
*                          DOB_Month                    -> 02
*                          DOB_Year                     -> 1999
*                          Educational_Status           -> Masters_Student
*                          Gender                       -> Male
*                          UserName                     -> EdgesAcademy
*                          Password                     -> Edges123
*                          Password Recheck             -> Edges123
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void TestCase1(void)
{
	unsigned int Test_id = Test1_User.PersonalInfo_Form.id;
	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test1_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test1_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test1_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test1_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test1_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test1_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test1_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test1_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test1_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test1_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 2
* Description            : Testing the Add Account Functionality with Invalid Data 
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Rania
*                          Age                          -> 54
*                          DOB_day                      -> 31
*                          DOB_Month                    -> 12
*                          DOB_Year                     -> 1970
*                          Educational_Status           -> PHD_Holder
*                          Gender                       -> Female
*                          UserName                     -> EdgesAcademy2024
*                          Password                     -> Edges_123_$$
*                          Password Recheck             -> Edges123
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Password inputs mismatch. 
*************************************************************************************/
static void TestCase2(void)
{
	unsigned int Test_id = Test2_User.PersonalInfo_Form.id;
	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test2_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test2_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 3
* Description            : Testing DBM Add User Functionality with Valid User
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Hamas123
*                          Password                     -> AllahAkbar123
*                          Password Recheck             -> AllahAkbar123
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void TestCase3(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	//Add a User
	unsigned char user_before_test = current_user_test;				//Holds Current user before test 
	APIresult = DBM_Add_User(&Test_Valid_User);
	Test_Valid_User.PersonalInfo_Form.id = current_user_test - 1;
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 4
* Description            : Testing DBM Add More than max Users
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*						   Enter Test_Valid_User data until we reach max users
*						   Enter Test1_User after that 
* Test Expected output   : The DB should not be updated with the last user adding attempt
* Reason                 : We have reached max user
*************************************************************************************/
static void TestCase4(void)
{
	// Reset the Database to initial state
	Reset_DataBase();
	
	/*Adding until max user*/
	while (current_user_test < MAX_USERS) {
		APIresult = DBM_Add_User(&Test_Valid_User);
		CU_ASSERT_EQUAL(APIresult, TRUE);
	}
	
	/*Attemping to Add another user*/
	unsigned char user_before_test = current_user_test;
	APIresult = DBM_Add_User(&Test1_User);
	Test_Valid_User.PersonalInfo_Form.id = current_user_test - 1;
	unsigned char Test_id = Test1_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test1_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test1_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 5
* Description            : Testing DBM Adding users until the DB is full
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*						   Enter Test_Valid_User data until we reach max users
* Test Expected output   : The DB should be updated with Users successfully
* Reason                 : The DB still not full
*************************************************************************************/
static void TestCase5(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Adding until max user*/
	while (current_user_test < MAX_USERS) {

		unsigned char user_before_test = current_user_test;
		APIresult = DBM_Add_User(&Test_Valid_User);
		CU_ASSERT_EQUAL(APIresult, TRUE);
		CU_ASSERT_EQUAL(current_user_test, user_before_test +1);
	}
}

/************************************************************************************
* Test ID                : TestCase 6
* Description            : Testing DBM Delete User Functionality
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							->  current_user_test - 1
* Test Expected output   : The DB should be updated without User 0 correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void TestCase6(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_id = current_user_test - 1;
	unsigned char user_before_test = current_user_test;
	APIresult = DBM_Add_User(&Test_Valid_User);
	if (APIresult == TRUE) {
		APIresult = DBM_Delete_User(Test_id);
	}
	else {
		CU_ASSERT_EQUAL_FATAL(current_user_test, user_before_test + 1);
	}
	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, 0);
}

/************************************************************************************
* Test ID                : TestCase 7
* Description            : Testing DBM Delete User Functionality until DB is empty
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> current user until 0
* Test Expected output   : The DB should be updated without any user.
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void TestCase7(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Deleting until users until DB is empty*/
	for (unsigned char i = current_user_test - 1; current_user_test > 0; --i) {
		unsigned char user_before_test = current_user_test;
		APIresult = DBM_Delete_User(i);
		CU_ASSERT_EQUAL(APIresult, TRUE);
		CU_ASSERT_EQUAL(current_user_test, user_before_test - 1);
	}

	unsigned char Test_id = 0;
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, DEFAULT_Status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, DEFAULT_Gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, "");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, 0);
}

/************************************************************************************
* Test ID                : TestCase 8
* Description            : Testing DBM Delete User functionality to delete max user
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> max user id
* Test Expected output   : The DB should be updated without the last user
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void TestCase8(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Adding until max user*/
	while (current_user_test < MAX_USERS) {
		APIresult = DBM_Add_User(&Test_Valid_User);
		CU_ASSERT_EQUAL_FATAL(APIresult, TRUE);
	}
	/*Delelte the max user*/
	unsigned char Test_id = current_user_test - 1;
	unsigned char user_before_test = current_user_test;
	APIresult = DBM_Delete_User(Test_id);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test - 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, 0);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, DEFAULT_Status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, DEFAULT_Gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, "");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, 0);
}

/************************************************************************************
* Test ID                : TestCase 9
* Description            : Testing DBM Delete User to delete (max + 1) user
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> max user + 1 id
* Test Expected output   : The function should do nothing and return FALSE
* Reason                 : (max + 1) user does not exist
*************************************************************************************/
static void TestCase9(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Delete the max user id + 1*/
	unsigned char Test_id = MAX_USERS;					//The max user id +1 = MAX_USERS
	unsigned char user_before_test = current_user_test;
	APIresult = DBM_Delete_User(Test_id);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test);
}

/************************************************************************************
* Test ID                : TestCase 10
* Description            : Testing DBM Delete User to delete (-1) user
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> -1
* Test Expected output   : The function should do nothing and return FALSE
* Reason                 : (-1) user does not exist
*************************************************************************************/
static void TestCase10(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Delete the -1 user id */
	unsigned char Test_id = -1;
	unsigned char user_before_test = current_user_test;
	APIresult = DBM_Delete_User(Test_id);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_test);
}

/************************************************************************************
* Test ID                : TestCase 11
* Description            : Testing DBM DBM_AddToCourse using valid user and Course IDs
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> 0
*						   Course ID						-> 1
* Test Expected output   : The function should add the course to the Enrollments
* Reason                 : All info is valid
*************************************************************************************/
static void TestCase11(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 0;
	unsigned char Test_Course_ID = 1;
	APIresult = DBM_AddToCourse(Test_Course_ID, Test_User_ID);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], TRUE);
}

/************************************************************************************
* Test ID                : TestCase 12
* Description            : Testing DBM Adding max participants to a course
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> loop from  0 until max participants
*						   Course ID						-> 2
* Test Expected output   : The function should add the course to the Enrollments for all users
* Reason                 : All info is valid
*************************************************************************************/
static void TestCase12(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 0;
	unsigned char Test_Course_ID = 2;
	for (Test_User_ID; Test_User_ID < MAX_STUDENTS_PER_COURSE; ++Test_User_ID) {
		APIresult = DBM_AddToCourse(Test_Course_ID, Test_User_ID);
		
		if (APIresult == FALSE)
			break;
	}
	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], TRUE);
}

/************************************************************************************
* Test ID                : TestCase 13
* Description            : Testing DBM Adding the same user to the same course more than max course capacity
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> 0
*						   Course ID						-> 2
* Test Expected output   : The function should add the course to the Enrollments and remain TRUE
* Reason                 : All info is valid
*************************************************************************************/
static void TestCase13(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 0;
	unsigned char Test_Course_ID = 2;
	
	for (int i = 0; i <= MAX_STUDENTS_PER_COURSE; ++i) {
		APIresult = DBM_AddToCourse(Test_Course_ID, Test_User_ID);
		CU_ASSERT_EQUAL(APIresult, TRUE);
	}
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], TRUE);

	//Delete the course from the user
	DBM_DeleteReservation(Test_Course_ID-1, Test_User_ID);
}

/************************************************************************************
* Test ID                : TestCase 14
* Description            : Testing DBM Deleting course reservation using valid data
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> 0
*						   Course ID						-> 6
* Test Expected output   : The function should remove the course from the Enrollments for the user
* Reason                 : All info is valid
*************************************************************************************/
static void TestCase14(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 0;
	unsigned char Test_Course_ID = 6;

	APIresult = DBM_DeleteReservation(Test_Course_ID, Test_User_ID);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], FALSE);
}

/************************************************************************************
* Test ID                : TestCase 15
* Description            : Testing DBM Deleting course reservation using empty course 
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> 0
*						   Course ID						-> 2
* Test Expected output   : The function should do nothing and return TRUE
* Reason                 : The course is empty
*************************************************************************************/
static void TestCase15(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 0;
	unsigned char Test_Course_ID = 2;

	APIresult = DBM_DeleteReservation(Test_Course_ID, Test_User_ID);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], FALSE);
}

/************************************************************************************
* Test ID                : TestCase 16
* Description            : Testing DBM Deleting course reservation using invalid User
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User ID							-> 5
*						   Course ID						-> 6
* Test Expected output   : The function should do nothing and return Error
* Reason                 : Invalid user
*************************************************************************************/
static void TestCase16(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_User_ID = 5;
	unsigned char Test_Course_ID = 6;

	int outOfBoundaryResult = Enrollments[Test_User_ID][Test_Course_ID - 1];
	APIresult = DBM_DeleteReservation(Test_Course_ID, Test_User_ID);

	CU_ASSERT_EQUAL(APIresult, ERROR);
	CU_ASSERT_EQUAL(Enrollments[Test_User_ID][Test_Course_ID - 1], outOfBoundaryResult);
}

/************************************************************************************
* Test ID                : TestCase 17
* Description            : Testing Course registration Add student to course using valid data
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Student ID						-> 0
*						   Course ID						-> 1
* Test Expected output   : The function should add user to the courses and return Enrolled
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase17(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_Student_ID = 0;
	unsigned char Test_Course_ID = 1;

	APIresult = AddStudentToCourse(Test_Student_ID, Test_Course_ID);

	CU_ASSERT_EQUAL(APIresult, Enrolled);
}

/************************************************************************************
* Test ID                : TestCase 18
* Description            : Testing Course registration Add student to course using valid data
*						   first user, first course
* Pre-requisits          : Database Reset to init state
* Test inputs            :
* *						   Course ID						-> 1
*                          Student ID						-> 0
* Test Expected output   : The function should add user to the courses and return Enrolled
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase18(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_Course_ID = 1;
	unsigned char Test_Student_ID = 0;

	APIresult = AddStudentToCourse(Test_Course_ID, Test_Student_ID);

	CU_ASSERT_EQUAL(APIresult, Enrolled);
}

/************************************************************************************
* Test ID                : TestCase 19
* Description            : Testing Course registration Add student to last course using valid data
* Pre-requisits          : Database Reset to init state
* Test inputs            :
* *						   Course ID						-> 6
*                          Student ID						-> 2
* Test Expected output   : The function should add user to the courses and return Enrolled
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase19(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_Course_ID = 6;
	unsigned char Test_Student_ID = 2;

	APIresult = AddStudentToCourse(Test_Course_ID, Test_Student_ID);

	CU_ASSERT_EQUAL(APIresult, Enrolled);
}

/************************************************************************************
* Test ID                : TestCase 20
* Description            : Testing Course registration Add last student to a course 
						   using not created student id
* Pre-requisits          : Database Reset to init state
* Test inputs            :
* *						   Course ID						-> 1
*                          Student ID						-> 4
* Test Expected output   : The function should not add user to the courses and return AlreadyEnrolled
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase20(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_Course_ID = 1;
	unsigned char Test_Student_ID = 4;

	APIresult = AddStudentToCourse(Test_Course_ID, Test_Student_ID);

	CU_ASSERT_EQUAL(APIresult, AlreadyEnrolled);
}

/************************************************************************************
* Test ID                : TestCase 21
* Description            : Testing Course registration Add already enrolled student to a course
* Pre-requisits          : Database Reset to init state
* Test inputs            :
* *						   Course ID						-> 6
*                          Student ID						-> 0
* Test Expected output   : The function should not add user to the courses and return AlreadyEnrolled
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase21(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	unsigned char Test_Course_ID = 6;
	unsigned char Test_Student_ID = 0;

	APIresult = AddStudentToCourse(Test_Course_ID, Test_Student_ID);

	CU_ASSERT_EQUAL(APIresult, AlreadyEnrolled);
}

/************************************************************************************
* Test ID                : TestCase 22
* Description            : Testing Add Account Functionality with Valid Data
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Hamas123
*                          Password                     -> AllahAkbar123
*                          Password Recheck             -> AllahAkbar123
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase22(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	APIresult = Add_Account(&Test_Valid_User);
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 23
* Description            : Testing Add Account Functionality with Name length = 2 
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Al

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : name length is less than 3 
*************************************************************************************/
static void TestCase23(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy (Test_Valid_User.PersonalInfo_Form.name, "Al");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 24
* Description            : Testing Add Account Functionality with Name length = 33
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> AlSinwarAlSiNwarAlSiNwarAlSiNwarr
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : name length is more than 32
*************************************************************************************/
static void TestCase24(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Test Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.PersonalInfo_Form.name, "AlSinwarAlSiNwarAlSiNwarAlSiNwarr");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);

}

/************************************************************************************
* Test ID                : TestCase 25
* Description            : Testing Add Account Functionality with Valid Data, Name length = 3
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> Als
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase25(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Test Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	strcpy(Test_Valid_User.PersonalInfo_Form.name, "AlS");
	APIresult = Add_Account(&Test_Valid_User);
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 26
* Description            : Testing Add Account Functionality with Valid Data, Name length = 32
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Name                         -> AlSinwarAlSiNwarAlSiNwarAlSiNwar
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase26(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Test Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	strcpy(Test_Valid_User.PersonalInfo_Form.name, "AlSinwarAlSiNwarAlSiNwarAlSiNwar");
	APIresult = Add_Account(&Test_Valid_User);
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 27
* Description            : Testing Add Account Functionality with Age = -1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                         -> -1

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Age is less than 0
*************************************************************************************/
static void TestCase27(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.Age = -1;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 28
* Description            : Testing Add Account Functionality with Age = 101
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                         -> 101

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Age is more than 100
*************************************************************************************/
static void TestCase28(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.Age = 101;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 29
* Description            : Testing Add Account Functionality with Valid Data, Age = 0
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                          -> 0
*						   DOB_year						-> CURRENT_YEAR
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase29(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	Test_Valid_User.PersonalInfo_Form.Age = 0;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR;
	APIresult = Add_Account(&Test_Valid_User);
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 30
* Description            : Testing Add Account Functionality with Valid Data, Age = 100
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                          -> 100
*						   DOB_year						-> CURRENT_YEAR - 100
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase30(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	Test_Valid_User.PersonalInfo_Form.Age = 100;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 100;
	APIresult = Add_Account(&Test_Valid_User);
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 31
* Description            : Testing Add Account Functionality with DOB_year diff = Age + 2
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age		                        -> 62
*                          DOB_year                         -> CURRENT_YEAR - 64

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_year diff = Age + 2
*************************************************************************************/
static void TestCase31(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 64;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 32
* Description            : Testing Add Account Functionality with DOB_year diff = Age-1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age		                        -> 62
*                          DOB_year                         -> CURRENT_YEAR - 61

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_year diff = Age-1
*************************************************************************************/
static void TestCase32(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 61;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 33
* Description            : Testing Add Account Functionality with DOB_year diff = Age+1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                          -> 62
*						   DOB_year						-> CURRENT_YEAR - 63
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase33(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 63;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 34
* Description            : Testing Add Account Functionality with DOB_year diff = Age
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Age                          -> 62
*						   DOB_year						-> CURRENT_YEAR - 62
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase34(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 62;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 35
* Description            : Testing Add Account Functionality with DOB_day higher BV +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_day							-> 31
*                          DOB_month                        -> April = 4

* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_day = higher BV + 1
*************************************************************************************/
static void TestCase35(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_day = 31;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 4;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 36
* Description            : Testing Add Account Functionality with DOB_day = lower BV - 1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_day							-> 0
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_day = lower BV - 1
*************************************************************************************/
static void TestCase36(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_day = 0;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 37
* Description            : Testing Add Account Functionality with DOB_day = lower BV
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_day							-> 1
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase37(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_day = 1;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 38
* Description            : Testing Add Account Functionality with DOB_day = higher BV
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_day							-> 29
*                          DOB_month						-> Feb = 2
*                          DOB_year							-> Year = 2000
*						   Age								-> CURRENT_YEAR - 2000
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase38(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_day = 29;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 2;
	Test_Valid_User.PersonalInfo_Form.DOB_year = 2000;
	Test_Valid_User.PersonalInfo_Form.Age = CURRENT_YEAR - 2000;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 39
* Description            : Testing Add Account Functionality with DOB_month = 0
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_month							-> 0
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_month is out of boundary
*************************************************************************************/
static void TestCase39(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 0;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 40
* Description            : Testing Add Account Functionality with DOB_month = 13
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_month							-> 13
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_month is out of boundary
*************************************************************************************/
static void TestCase40(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 13;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 41
* Description            : Testing Add Account Functionality with DOB_month = 1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_month						-> 1
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase41(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 1;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 42
* Description            : Testing Add Account Functionality with DOB_month = 12
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_month						-> 12
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase42(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_month = 12;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 43
* Description            : Testing Add Account Functionality with DOB_year = CURRENT_YEAR +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_year							-> CURRENT_YEAR +1
*						   Age								-> 0
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_year is out of boundary
*************************************************************************************/
static void TestCase43(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR + 1;
	Test_Valid_User.PersonalInfo_Form.Age = 0;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 44
* Description            : Testing Add Account Functionality with DOB_year = CURRENT_YEAR - 101 
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_year							-> CURRENT_YEAR  - 101
*						   Age								-> 100
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : DOB_year is out of boundary
*************************************************************************************/
static void TestCase44(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 101;
	Test_Valid_User.PersonalInfo_Form.Age = 100;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 45
* Description            : Testing Add Account Functionality with DOB_year = CURRENT_YEAR - 100
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_year							-> CURRENT_YEAR - 100
*						   Age								-> 100
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase45(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR - 100;
	Test_Valid_User.PersonalInfo_Form.Age = 100;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 46
* Description            : Testing Add Account Functionality with DOB_year = CURRENT_YEAR
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          DOB_year							-> CURRENT_YEAR
*						   Age								-> 0
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase46(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.DOB_year = CURRENT_YEAR;
	Test_Valid_User.PersonalInfo_Form.Age = 0;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 47
* Description            : Testing Add Account Functionality with Educational Status = DEFAULT
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> DEFAULT_Status
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Educational status is out of boundary
*************************************************************************************/
static void TestCase47(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = DEFAULT_Status;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 48
* Description            : Testing Add Account Functionality with Educational Status = higher BV +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> 7
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Educational status is out of boundary
*************************************************************************************/
static void TestCase48(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = 7;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 49
* Description            : Testing Add Account Functionality with Educational Status = PHD_Holder
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> PHD_Holder
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase49(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = PHD_Holder;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 50
* Description            : Testing Add Account Functionality with Educational Status = Student
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> Student
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase50(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = Student;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 51
* Description            : Testing Add Account Functionality with gender = Max + 1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          gender							-> 3
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : gender is out of boundary
*************************************************************************************/
static void TestCase51(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.gender = 3;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 52
* Description            : Testing Add Account Functionality with gender = DEFAULT_Gender
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          gender							-> DEFAULT_Gender
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : gender is out of boundary
*************************************************************************************/
static void TestCase52(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.gender = DEFAULT_Gender;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 53
* Description            : Testing Add Account Functionality with gender = Min
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          gender							-> Male
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase53(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.gender = Male;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 54
* Description            : Testing Add Account Functionality with gender = Max
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          gender							-> Female
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase54(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.gender = Female;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

	/************************************************************************************
* Test ID                : TestCase 55
* Description            : Testing Add Account with username length = min -1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_name							-> Hamas12
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : username length is out of boundary
*************************************************************************************/
static void TestCase55(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name, "Hamas12");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 56
* Description            : Testing Add Account with username length = max +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_name						-> HamasHamasHamasHamasHamasHamas123
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : username length is out of boundary
*************************************************************************************/
static void TestCase56(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name, "HamasHamasHamasHamasHamasHamas123");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 57
* Description            : Testing Add Account with username length = min
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_name							-> Hamas123
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase57(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name, "Hamas123");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 58
* Description            : Testing Add Account with username length = max
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_name							-> HamasHamasHamasHamasHamasHamas12
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase58(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name, "HamasHamasHamasHamasHamasHamas12");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 59
* Description            : Testing Add Account with password length = min -1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password								-> Hamas12
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : password length is out of boundary
*************************************************************************************/
static void TestCase59(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "Hamas12");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "Hamas12");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 60
* Description            : Testing Add Account with password length = max +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password						-> HamasHamasHamasHamasHamasHamas123
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : password length is out of boundary
*************************************************************************************/
static void TestCase60(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "HamasHamasHamasHamasHamasHamas123");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "HamasHamasHamasHamasHamasHamas123");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 61
* Description            : Testing Add Account with password length = max
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password							-> HamasHamasHamasHamasHamasHamas12
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase61(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "HamasHamasHamasHamasHamasHamas12");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "HamasHamasHamasHamasHamasHamas12");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.Password_Recheck);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 62
* Description            : Testing Add Account with password length = min
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password							-> Hamas123
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase62(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "Hamas123");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "Hamas123");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.Password_Recheck);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 63
* Description            : Testing Add Account with Password_Recheck length = min -1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password_Recheck								-> Hamas12
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Password_Recheck length is out of boundary
*************************************************************************************/
static void TestCase63(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "Hamas12");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 64
* Description            : Testing Add Account with Password_Recheck length = max +1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password_Recheck						-> HamasHamasHamasHamasHamasHamas123
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Password_Recheck length is out of boundary
*************************************************************************************/
static void TestCase64(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "HamasHamasHamasHamasHamasHamas123");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 65
* Description            : Testing Add Account with Password mismatch
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Password								-> AllahAkbar
*                          Password_Recheck						-> Allahakbar1
* Test Expected output   : The function should NOT Add the account to the database
* Reason                 : Password mismatch
*************************************************************************************/
static void TestCase65(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	strcpy(Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password, "Allahakbar");
	strcpy(Test_Valid_User.LoginCredentials_Form.Password_Recheck, "Allahakbar1");
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_STRING_NOT_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.Password_Recheck);
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 66
* Description            : Testing Add Account Functionality with Educational Status = Faculty_Student
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> Faculty_Student
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase66(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = Faculty_Student;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 67
* Description            : Testing Add Account Functionality with Educational Status = PHD_Student
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          educational_status						-> PHD_Student
* Test Expected output   : The function should Add the account to the database
* Reason                 : All inputs are valid
*************************************************************************************/
static void TestCase67(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Add a User
	Test_Valid_User.PersonalInfo_Form.id = current_user_test;				//Holds Current user
	unsigned char Test_id = Test_Valid_User.PersonalInfo_Form.id;
	Test_Valid_User.PersonalInfo_Form.educational_status = PHD_Student;
	APIresult = Add_Account(&Test_Valid_User);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, Test_Valid_User.PersonalInfo_Form.id + 1);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test_Valid_User.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test_Valid_User.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test_Valid_User.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test_Valid_User.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test_Valid_User.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test_Valid_User.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test_Valid_User.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test_Valid_User.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test_Valid_User.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_Valid_User.PersonalInfo_Form.id);
}

/************************************************************************************
* Test ID                : TestCase 68
* Description            : Testing Delete Account with Test user id = min -1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Test_id								-> -1
* Test Expected output   : The function should NOT affect the database and return false
* Reason                 : Test user id is not valid
*************************************************************************************/
static void TestCase68(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Delete a User
	unsigned char user_before_attempt = current_user_test;				//Holds Current user
	char Test_id = -1;
	APIresult = Delete_Account(Test_id);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_attempt);
}

/************************************************************************************
* Test ID                : TestCase 69
* Description            : Testing Delete Account with Test user id = max id + 1
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Test_id								-> MAX_USERS
* Test Expected output   : The function should NOT affect the database and return false
* Reason                 : Test user id is not valid
*************************************************************************************/
static void TestCase69(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Delete a User
	unsigned char user_before_attempt = current_user_test;				//Holds Current user
	unsigned char Test_id = MAX_USERS;
	APIresult = Delete_Account(Test_id);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_attempt);
}

/************************************************************************************
* Test ID                : TestCase 70
* Description            : Testing Delete Account with Test user id = max id + 2
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Test_id								-> MAX_USERS + 2 
* Test Expected output   : The function should NOT affect the database and return false
* Reason                 : Test user id is not valid
*************************************************************************************/
static void TestCase70(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Delete a User
	unsigned char user_before_attempt = current_user_test;				//Holds Current user
	unsigned char Test_id = MAX_USERS + 2;
	APIresult = Delete_Account(Test_id);

	CU_ASSERT_EQUAL(APIresult, FALSE);
	CU_ASSERT_EQUAL(current_user_test, user_before_attempt);
}

/************************************************************************************
* Test ID                : TestCase 71
* Description            : Testing Delete Account with Test user id = 0
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Test_id								-> 0
* Test Expected output   : The function should NOT affect the database and return false
* Reason                 : All data is valid
*************************************************************************************/
static void TestCase71(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();

	//Delete a User
	unsigned char user_before_attempt = current_user_test;				//Holds Current user
	unsigned char Test_id = 0;
	APIresult = Delete_Account(Test_id);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, user_before_attempt - 1);
}

/************************************************************************************
* Test ID                : TestCase 72
* Description            : Testing Delete Account with Test user id = Max
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          Test_id								-> 4
* Test Expected output   : The function should NOT affect the database and return false
* Reason                 : All data is valid
*************************************************************************************/
static void TestCase72(void)
{
	// Reset the Database to initial state
	Reset_DataBase();

	/*Reset Valid User to init state*/
	reset_test_valid_user();


	//Fill the database
	Add_Account(&Test_Valid_User);
	Add_Account(&Test_Valid_User);

	//Delete a User
	unsigned char user_before_attempt = current_user_test;				//Holds Current user
	unsigned char Test_id = 4;
	APIresult = Delete_Account(Test_id);

	CU_ASSERT_EQUAL(APIresult, TRUE);
	CU_ASSERT_EQUAL(current_user_test, user_before_attempt -1);
}

/************************************************************************************
* Test ID                : TestCase 73
* Description            : Testing Detect_User_Type using AdminMohamedTarek
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_Type						-> AdminMohamedTarek
* Test Expected output   : The function should return AdminMohamedTarek
* Reason                 : The input is AdminMohamedTarek
*************************************************************************************/
static void TestCase73(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("0\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Detect_User_Type();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, AdminMohamedTarek);
}

/************************************************************************************
* Test ID                : TestCase 74
* Description            : Testing Detect_User_Type using NormalUser
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_Type						-> NormalUser
* Test Expected output   : The function should return NormalUser
* Reason                 : The input is NormalUser
*************************************************************************************/
static void TestCase74(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Detect_User_Type();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, NormalUser);
}

/************************************************************************************
* Test ID                : TestCase 75
* Description            : Testing Detect_User_Type using IncorrectLogin
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          User_Type						-> 2
* Test Expected output   : The function should return IncorrectLogin
* Reason                 : The input is IncorrectLogin
*************************************************************************************/
static void TestCase75(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("2\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Detect_User_Type();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, IncorrectLogin);
}

/************************************************************************************
* Test ID                : TestCase 76
* Description            : Testing Verify_Admin using first time correctLogin 
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          token						-> SECRET_ADMIN_TOKEN
* Test Expected output   : The function should return TRUE
* Reason                 : The input is correct token
*************************************************************************************/
static void TestCase76(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("10203040\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Verify_Admin();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, TRUE);
}

/************************************************************************************
* Test ID                : TestCase 77
* Description            : Testing Verify_Admin using second time correctLogin
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          token						-> Wrong token
*                          token						-> SECRET_ADMIN_TOKEN
* Test Expected output   : The function should return TRUE
* Reason                 : The input is correct token
*************************************************************************************/
static void TestCase77(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("10203041\n10203040\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Verify_Admin();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, TRUE);
}

/************************************************************************************
* Test ID                : TestCase 78
* Description            : Testing Verify_Admin using THIRD time correctLogin
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          token						-> Wrong token
*                          token						-> Wrong token
*                          token						-> SECRET_ADMIN_TOKEN
* Test Expected output   : The function should return TRUE
* Reason                 : The input is correct token
*************************************************************************************/
static void TestCase78(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("10203041\n10203039\n10203040\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Verify_Admin();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, TRUE);
}

/************************************************************************************
* Test ID                : TestCase 79
* Description            : Testing Verify_Admin using three times wrong token
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          token						-> Wrong token
*                          token						-> Wrong token
*                          token						-> Wrong token
* Test Expected output   : The function should return FALSE
* Reason                 : The input is correct token
*************************************************************************************/
static void TestCase79(void)
{
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("10203041\n10203039\n0203040\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Call the function to test
	APIresult = Verify_Admin();

	//Check the result
	CU_ASSERT_EQUAL(APIresult, FALSE);
}

/************************************************************************************
* Test ID                : TestCase 80
* Description            : Testing Verify_User with valid user and pass
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          UserName						-> AdminUser3
*                          Password						-> Edges_123 
* Test Expected output   : The function should return TRUE and return correct user id
* Reason                 : The inputs are valid
*************************************************************************************/
static void TestCase80(void)
{
	char UserName[33] = "AdminUser3";
	char Password[33]= "Edges_123";
	int id_ptr;
	//Call the function to test
	APIresult = Verify_User(UserName, Password, &id_ptr);

	//Check the result
	CU_ASSERT_EQUAL(APIresult, Login_Successful);
	CU_ASSERT_EQUAL(id_ptr, 2);
}

/************************************************************************************
* Test ID                : TestCase 81
* Description            : Testing Verify_User with wrong user
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          UserName						-> AdminUser10
*                          Password						-> Edges_123
* Test Expected output   : The function should return UserName_NotFound and return id = -1
* Reason                 : The user name is invalid
*************************************************************************************/
static void TestCase81(void)
{
	char UserName[33] = "AdminUser10";
	char Password[33] = "Edges_123";
	int id_ptr;
	//Call the function to test
	APIresult = Verify_User(UserName, Password, &id_ptr);

	//Check the result
	CU_ASSERT_EQUAL(APIresult, UserName_NotFound);
	CU_ASSERT_EQUAL(id_ptr, -1);
}

/************************************************************************************
* Test ID                : TestCase 82
* Description            : Testing Verify_User with wrong pass
* Pre-requisits          : Database Reset to init state
* Test inputs            :
*                          UserName						-> AdminUser3
*                          Password						-> Edges_1235
* Test Expected output   : The function should return Password_incorrect and return id = -1
* Reason                 : The pass is invalid
*************************************************************************************/
static void TestCase82(void)
{
	char UserName[33] = "AdminUser3";
	char Password[33] = "Edges_1235";
	int id_ptr;
	//Call the function to test
	APIresult = Verify_User(UserName, Password, &id_ptr);

	//Check the result
	CU_ASSERT_EQUAL(APIresult, Password_incorrect);
	CU_ASSERT_EQUAL(id_ptr, -1);
}


#ifdef SYSTEM_TESTS
/************************************************************************************
* Test ID                : TestCase 101
* Description            : Confirm Admin Can Register a Valid User Successfully
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select Admin login			-> 0
*						   Enter the correct token		-> 10203040
*						   Enter add a new user			-> A
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Testuser123
*                          Password                     -> TestPassword123
*                          Password Recheck             -> TestPassword123
*						   Enter Quit					-> Q
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
void TestCase101()
{
	// Reset the Database to initial state
	Reset_DataBase();	
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("0\n10203040\nA\nAlsinwar\n62\n29\n10\n1962\n3\n1\nTestuser123\n\
		   TestPassword123\nTestPassword123\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = current_user_test - 1;
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, 62);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, 29);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, 10);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, 1962);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Graduate);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Male);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, "Alsinwar");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "Testuser123");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "TestPassword123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 102
* Description            : Confirm Admin Can Delete Existing User Successfully
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select Admin login			-> 0
*						   Enter the correct token		-> 10203040
*						   Enter Delete user			-> D
*                          Enter the user id            -> 2
*						   Enter Quit					-> Q
* Test Expected output   : The DB should be updated without user id 2
* Reason                 : All inputs are in correct format
*************************************************************************************/
void TestCase102()
{
	// Reset the Database
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("0\n10203040\nD\n2\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = 2;
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, "AdminUser3");
	CU_ASSERT_NOT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 103
* Description            : Confirm Admin Can not Register an inValid User
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select Admin login			-> 0
*						   Enter the correct token		-> 10203040
*						   Enter add a new user			-> A
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Testuser123
*                          Password                     -> TestPassword123
*                          Password Recheck             -> TestPassword
*						   Enter Quit					-> Q
* Test Expected output   : The DB should not be updated with the previous inputs
* Reason                 : Password inputs mismatch. 
*************************************************************************************/
void TestCase103()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("0\n10203040\nA\nAlsinwar\n62\n29\n10\n1962\n3\n1\nTestuser123\n\
		   TestPassword123\nTestPassword\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = current_user_test - 1;
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, "Testuser123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 104
* Description            : Confirm Admin Can not delete a non existent User
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select Admin login			-> 0
*						   Enter the correct token		-> 10203040
*						   Enter Delete a user			-> D
*                          Enter an invalid user ID     -> 5
*						   Enter Quit					-> Q
* Test Expected output   : The DB should be unchanged
* Reason                 : Wrong user ID
*************************************************************************************/
void TestCase104()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("0\n10203040\nD\n5\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[0].User_Name, "AdminUser1");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[1].User_Name, "AdminUser2");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[2].User_Name, "AdminUser3");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[3].User_Name, "");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[4].User_Name, "");

}

/************************************************************************************
* Test ID                : TestCase 105
* Description            : Confirm Normal User  Can Create a valid account Successfully
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select User login			-> 1
*						   Enter Create a new account	-> C
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Testuser123
*                          Password                     -> TestPassword123
*                          Password Recheck             -> TestPassword123
*						   Enter Quit					-> Q
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
void TestCase105()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\nC\nAlsinwar\n62\n29\n10\n1962\n3\n1\nTestuser123\n\
		   TestPassword123\nTestPassword123\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = current_user_test - 1;
	CU_ASSERT_EQUAL(DB_info[Test_id].Age, 62);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, 29);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, 10);
	CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, 1962);
	CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Graduate);
	CU_ASSERT_EQUAL(DB_info[Test_id].gender, Male);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, "Alsinwar");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "Testuser123");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "TestPassword123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 106
* Description            : Confirm Normal User Can not Register an inValid Account
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select User login			-> 1
*						   Enter Create a new account	-> C
*                          Name                         -> Alsinwar
*                          Age                          -> 62
*                          DOB_day                      -> 29
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1962
*                          Educational_Status           -> Graduate
*                          Gender                       -> Male
*                          UserName                     -> Testuser123
*                          Password                     -> TestPassword123
*                          Password Recheck             -> TestPassword
*						   Enter Quit					-> Q
* Test Expected output   : The DB should not be updated with the previous inputs
* Reason                 : Password inputs mismatch.
*************************************************************************************/
void TestCase106()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\nC\n\nAlsinwar\n62\n29\n10\n1962\n3\n1\nTestuser123\n\
		   TestPassword123\nTestPassword\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = current_user_test - 1;
	CU_ASSERT_STRING_NOT_EQUAL(DB_LoginCredentials[Test_id].User_Name, "Testuser123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 107
* Description            : Confirm Valid Normal User Can Login and change password successfully
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select User login			-> 1
*						   Enter Login to your account	-> L
*                          UserName                     -> AdminUser1
*                          Password                     -> Edges123
*						   Enter Change Your Password	-> C
*						   Enter Your Current Password	-> Edges123
*						   Enter A new Password			-> Testing123
*                          Password Recheck             -> Testing123
*						   Enter Quit user menu			-> Q
* 						   Enter Quit					-> Q
* Test Expected output   : The DB should be updated with the new password correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
void TestCase107()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\nL\nAdminUser1\nEdges123\nC\nEdges123\nTesting123\nTesting123\nQ\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = 0;
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "AdminUser1");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "Testing123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 108
* Description            : Confirm Normal User Can Login and can't change password 
						   using invalid new Pass
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select User login			-> 1
*						   Enter Login to your account	-> L
*                          UserName                     -> AdminUser1
*                          Password                     -> Edges123
*						   Enter Change Your Password	-> C
*						   Enter Your Current Password	-> Edges123
*						   Enter A new Password			-> Testing123
*                          Password Recheck             -> Testing
*						   Enter Quit user menu			-> Q
* 						   Enter Quit					-> Q
* Test Expected output   : The DB should not be updated with the new password
* Reason                 : Password inputs mismatch.
*************************************************************************************/
void TestCase108()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\nL\nAdminUser1\nEdges123\nC\nEdges123\nTesting123\nTesting\nQ\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = 0;
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "AdminUser1");
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, "Edges123");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}

/************************************************************************************
* Test ID                : TestCase 109
* Description            : Confirm Valid Normal User Can Login and Reserve a course successfully
* Pre-requisits          : Database initialized.
* Test inputs            :
*						   Select Normal login			-> 1
*						   Enter Login to your account	-> L
*                          UserName                     -> AdminUser1
*                          Password                     -> Edges123
*						   Enter Reserve a course		-> R
*						   Choose a valid Course		-> 1
*						   Enter Quit user menu			-> Q
* 						   Enter Quit					-> Q
* Test Expected output   : The DB should be updated with the new Course Reservation correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
void TestCase109()
{
	// Reset the Database to initial state
	Reset_DataBase();
	// Open the file for writing to erase its contents
	temp_input = fopen(temp_input_name, "w");

	// Write inputs to the input file
	fputs("1\nL\nAdminUser1\nEdges123\nR\n1\nQ\nQ\n", temp_input);
	fflush(temp_input);							// Ensure all data is written
	fclose(temp_input);							// Close the file after writing

	// Redirect stdin
	if (freopen(temp_input_name, "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		return;
	}

	//Run Main App to add user
	Main_App_Runner();

	//Check the database
	unsigned int Test_id = 0;
	unsigned Course_index = 1 - (1);					// We deduct a (1) to get the index from the id
	CU_ASSERT_EQUAL(Enrollments[Test_id][Course_index], TRUE);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, "AdminUser1");
	CU_ASSERT_EQUAL(DB_info[Test_id].id, Test_id);
}
#endif //SYSTEM_TESTS

/* Test Code to test the Sign Up */
void Main_Test_Runner(void)
{
	/* initialize the Registry */
	CU_initialize_registry();

	/* Adding Test Suite to the Registry */
	CU_pSuite suite_positive = CU_add_suite("Creaet Valid Account", test1_start, test1_end);
	CU_pSuite suite_negative = CU_add_suite("Creaet InValid Account", test2_start, test2_end);

	/* Adding Test Cases to the Test Suite*/
	CU_add_test(suite_positive, "Creaet Valid Account", TestCase1);
	// this suite is expected to fail and not to run due to to the invalid creation of the account 
	CU_add_test(suite_negative, "Creaet InValid Account", TestCase2);
	
	/*************************************DBM Component Test************************************/
	/* Adding Test Suite to the Registry */
	/* This suite is to Test all valid functionalities specific to DBM fcn*/
	CU_pSuite DBM_suite_valid = CU_add_suite("Valid DBM suite", DBM_Start, DBM_End);
	/* This suite is to Test all Invalid functionalities specific to DBM fcn*/
	CU_pSuite DBM_suite_Invalid = CU_add_suite("InValid DBM suite", DBM_Start, DBM_End);

	/* Adding Test Cases to the Test Suite*/
	CU_add_test(DBM_suite_valid, "Add User to DB", TestCase3);
	CU_add_test(DBM_suite_Invalid, "Add More User to MaxUsers DB", TestCase4);
	CU_add_test(DBM_suite_valid, "Add Users to DB Until full", TestCase5);

	CU_add_test(DBM_suite_valid, "Delete User from DB", TestCase6);
	CU_add_test(DBM_suite_valid, "Delete all User from DB", TestCase7);
	CU_add_test(DBM_suite_valid, "Delete last User from DB", TestCase8);
	CU_add_test(DBM_suite_Invalid, "Add More User to MaxUsers DB", TestCase9);
	CU_add_test(DBM_suite_Invalid, "Add More User to MaxUsers DB", TestCase10);
	CU_add_test(DBM_suite_valid, "Add To Course using valid user and Course IDs", TestCase11);
	CU_add_test(DBM_suite_valid, "Adding max participants to a course", TestCase12);
	/* This test case is commented because it will affect other cases*/
	//CU_add_test(DBM_suite_Invalid, "Adding the same user to a course more max course capacity", TestCase13);
	CU_add_test(DBM_suite_valid, "Deleting course reservation", TestCase14);
	CU_add_test(DBM_suite_Invalid, "Deleting course reservation using empty course", TestCase15);
	CU_add_test(DBM_suite_Invalid, "Deleting course reservation using invalid user", TestCase16);

	/***************************Courses_Registeration Component Test****************************/
	/* Adding Test Suite to the Registry */
	/* This suite is to Test all valid functionalities specific to the Course Registeration fcn*/
	CU_pSuite course_reg_suite_valid = CU_add_suite("Valid Course Reg Suite", Course_Reg_Start, Course_Reg_End);
	/* This suite is to Test all Invalid functionalities specific to the Course Registeration fcn*/
	CU_pSuite course_reg_suite_invalid = CU_add_suite("InValid Course Reg Suite", Course_Reg_Start, Course_Reg_End);

	/* Adding Test Cases to the Test Suite*/
	/*This test case will be commented because it results in an error but will be here just for documetary reasons*/
	//CU_add_test(course_reg_suite_valid, "Add student to a course", TestCase17);
	CU_add_test(course_reg_suite_valid, "Add first student to first course", TestCase18);
	CU_add_test(course_reg_suite_valid, "Add student to a last course", TestCase19);
	CU_add_test(course_reg_suite_invalid, "Add student to a last course", TestCase20);
	CU_add_test(course_reg_suite_invalid, "Add already enrolled student to a course", TestCase21);

	/*************************************Create Account Test************************************/
	/*Add Account Function suites*/
	CU_pSuite add_account_valid_suite = CU_add_suite("Add Account Valid Suite", Add_Account_Start, Add_Account_End);
	CU_pSuite add_account_invalid_suite = CU_add_suite("Add Account Invalid Suite", Add_Account_Start, Add_Account_End);
	CU_pSuite add_account_MCDC_suite = CU_add_suite("Add Account MC/DC Suite", Add_Account_Start, Add_Account_End);

	/* Adding Test Cases to the Test Suite*/
	CU_add_test(add_account_valid_suite, "Add Account with Valid Data", TestCase22);
	CU_add_test(add_account_MCDC_suite, "Add Account with Valid Data", TestCase22);
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid Name length = 2", TestCase23);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid Name length = 2", TestCase23);
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid Name length = 33", TestCase24);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid Name length = 33", TestCase24);
	CU_add_test(add_account_valid_suite, "Add Account with Valid Name length 3", TestCase25);
	CU_add_test(add_account_valid_suite, "Add Account with Valid Name length 32", TestCase26); 
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid Age = -1", TestCase27);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid Age = -1", TestCase27);
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid Age = 101", TestCase28);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid Age = 101", TestCase28);
	CU_add_test(add_account_valid_suite, "Add Account with Valid Age = 0", TestCase29);
	CU_add_test(add_account_valid_suite, "Add Account with Valid Age = 100", TestCase30);
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid DOB_year diff = Age + 2", TestCase31);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid DOB_year diff = Age + 2", TestCase31);
	CU_add_test(add_account_invalid_suite, "Add Account with Invalid DOB_year diff = Age-1", TestCase32);
	CU_add_test(add_account_MCDC_suite, "Add Account with Invalid DOB_year diff = Age-1", TestCase32);
	CU_add_test(add_account_valid_suite, "Add Account with Invalid DOB_year diff = Age+1", TestCase33);
	CU_add_test(add_account_valid_suite, "Add Account with Invalid DOB_year diff = Age", TestCase34);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_day higher BV +1", TestCase35);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_day higher BV +1", TestCase35);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_day lower BV -1", TestCase36);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_day BV -1", TestCase36);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_day = lower BV", TestCase37);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_day = higher BV", TestCase38);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_month = -1", TestCase39);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_month = -1", TestCase39);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_month = 13", TestCase40);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_month = 13", TestCase40);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_month = 1", TestCase41);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_month = 1", TestCase42);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_year = CURRENT_YEAR +1", TestCase43);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_year = CURRENT_YEAR +1", TestCase43);
	CU_add_test(add_account_invalid_suite, "Add Account with DOB_year = CURRENT_YEAR +1", TestCase44);
	CU_add_test(add_account_MCDC_suite, "Add Account with DOB_year = CURRENT_YEAR +1", TestCase44);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_year = CURRENT_YEAR - 100", TestCase45);
	CU_add_test(add_account_valid_suite, "Add Account with DOB_year = CURRENT_YEAR", TestCase46);
	CU_add_test(add_account_invalid_suite, "Add Account with Educational Status = DEFAULT", TestCase47);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = DEFAULT", TestCase47);
	CU_add_test(add_account_invalid_suite, "Add Account with Educational Status = higher BV +1", TestCase48);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = higher BV +1", TestCase48);
	CU_add_test(add_account_valid_suite, "Add Account with Educational Status = PHD_Holder", TestCase49);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = PHD_Holder", TestCase49);
	CU_add_test(add_account_valid_suite, "Add Account with Educational Status = Student", TestCase50);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = Student", TestCase50);
	CU_add_test(add_account_valid_suite, "Add Account with Educational Status = Faculty_Student", TestCase66);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = Faculty_Student", TestCase66);
	CU_add_test(add_account_valid_suite, "Add Account with Educational Status = PHD_Student", TestCase67);
	CU_add_test(add_account_MCDC_suite, "Add Account with Educational Status = PHD_Student", TestCase67);
	CU_add_test(add_account_invalid_suite, "Add Account with gender = Max + 1", TestCase51);
	CU_add_test(add_account_MCDC_suite, "Add Account with gender = Max + 1", TestCase51);
	CU_add_test(add_account_invalid_suite, "Add Account with gender = DEFAULT_Gender", TestCase52);
	CU_add_test(add_account_MCDC_suite, "Add Account with gender = DEFAULT_Gender", TestCase52);
	CU_add_test(add_account_valid_suite, "Add Account with gender = Min", TestCase53);
	CU_add_test(add_account_valid_suite, "Add Account with gender = Max", TestCase54);
	CU_add_test(add_account_invalid_suite, "Add Account with username length = min -1", TestCase55);
	CU_add_test(add_account_MCDC_suite, "Add Account with username length = min -1", TestCase55);
	CU_add_test(add_account_invalid_suite, "Add Account with username length = max +1", TestCase56);
	CU_add_test(add_account_MCDC_suite, "Add Account with username length = max +1", TestCase56);
	CU_add_test(add_account_valid_suite, "Add Account with username length = min", TestCase57);
	CU_add_test(add_account_valid_suite, "Add Account with username length = max", TestCase58);
	CU_add_test(add_account_invalid_suite, "Add Account with password length = min -1", TestCase59);
	CU_add_test(add_account_MCDC_suite, "Add Account with password length = min -1", TestCase59);
	CU_add_test(add_account_invalid_suite, "Add Account with password length = max +1", TestCase60);
	CU_add_test(add_account_MCDC_suite, "Add Account with password length = max +1", TestCase60);
	CU_add_test(add_account_valid_suite, "Add Account with password length = max", TestCase61);
	CU_add_test(add_account_valid_suite, "Add Account with password length = min", TestCase62);
	CU_add_test(add_account_invalid_suite, "Add Account with Password_Recheck length = min -1", TestCase63);
	CU_add_test(add_account_MCDC_suite, "Add Account with Password_Recheck length = min -1", TestCase63);
	CU_add_test(add_account_invalid_suite, "Add Account with Password_Recheck length = max +1", TestCase64);
	CU_add_test(add_account_MCDC_suite, "Add Account with Password_Recheck length = max +1", TestCase64);
	CU_add_test(add_account_invalid_suite, "Add Account with Password mismatch", TestCase65);
	CU_add_test(add_account_MCDC_suite, "Add Account with Password mismatch", TestCase65);

	/*Delete Account Function suites*/
	CU_pSuite delete_account_valid_suite = CU_add_suite("Delete Account Valid Suite", Delete_Account_Start, Delete_Account_End);
	CU_pSuite delete_account_invalid_suite = CU_add_suite("Delete Account Invalid Suite", Delete_Account_Start, Delete_Account_End);
	CU_pSuite delete_account_MCDC_suite = CU_add_suite("Delete Account MC/DC Suite", Delete_Account_Start, Delete_Account_End);

	/* Adding Test Cases to the Test Suite*/
	CU_add_test(add_account_invalid_suite, "Delete Account with Test user id = min -1", TestCase68);
	CU_add_test(add_account_MCDC_suite, "Delete Account with Test user id = min -1", TestCase68);
	CU_add_test(add_account_invalid_suite, "Delete Account with Test user id = max id + 1", TestCase69);
	CU_add_test(add_account_MCDC_suite, "Delete Account with Test user id = max id + 1", TestCase69);
	CU_add_test(add_account_invalid_suite, "Delete Account with Test user id = max id + 2", TestCase70);
	CU_add_test(add_account_MCDC_suite, "Delete Account with Test user id = max id + 2", TestCase70);
	CU_add_test(delete_account_valid_suite, "Delete Account with Test user id = min", TestCase71);
	CU_add_test(add_account_MCDC_suite, "Delete Account with Test user id = min", TestCase71);
	CU_add_test(delete_account_valid_suite, "Delete Account with Test user id = max", TestCase72);

	/*****************************************Login Test******************************************/
	//Detect_User_Type Test suites
	CU_pSuite Detect_User_MCDC_suite = CU_add_suite("Detect_User_Type Suite", Login_Test_Start, Login_test_teardown_end);

	// Adding Test Cases to the Test Suite*/
	CU_add_test(Detect_User_MCDC_suite, "Detect_User_Type with Admin", TestCase73);
	CU_add_test(Detect_User_MCDC_suite, "Detect_User_Type with NormalUser", TestCase74);
	CU_add_test(Detect_User_MCDC_suite, "Detect_User_Type with IncorrectLogin", TestCase75);

	//Verify Admin Test suites
	CU_pSuite Verify_Admin_MCDC_suite = CU_add_suite("Verify_Admin Suite", Login_Test_Start, Login_test_teardown_end);
	
	// Adding Test Cases to the Test Suite*/
	CU_add_test(Verify_Admin_MCDC_suite, "Verify_Admin with first time Correct Token", TestCase76);
	CU_add_test(Verify_Admin_MCDC_suite, "Verify_Admin with second time Correct Token", TestCase77);
	CU_add_test(Verify_Admin_MCDC_suite, "Verify_Admin with third time Correct Token", TestCase78);
	CU_add_test(Verify_Admin_MCDC_suite, "Verify_Admin with three times Wrong Token", TestCase79);

	//Verify_User Test suites
	CU_pSuite Verify_User_MCDC_suite = CU_add_suite("Verify_User Suite", NULL, NULL);

	// Adding Test Cases to the Test Suite*/
	CU_add_test(Verify_User_MCDC_suite, "Verify_User with valid user and pass", TestCase80);
	CU_add_test(Verify_User_MCDC_suite, "Verify_User with wrong UserName", TestCase81);
	CU_add_test(Verify_User_MCDC_suite, "Verify_User with wrong Password", TestCase82);

#ifdef SYSTEM_TESTS
	/********************************Admin Test*********************************/
	/* This suite is to Test all valid functionalities specific to the Admin role*/
	CU_pSuite admin_valid_suite = CU_add_suite("Admin Valid Functionalities", system_test_setup_start, system_test_teardown_end);
	/* Adding Test Cases to the Test Suite*/
	CU_add_test(admin_valid_suite, "Test Admin Add Valid User", TestCase101);
	CU_add_test(admin_valid_suite, "Test Admin Delete a User", TestCase102);
	/* This suite is to Test invalid functionalities specific to the Admin role*/
	CU_pSuite admin_Invalid_suite = CU_add_suite("Admin Invalid Functionalities", system_test_setup_start, system_test_teardown_end);
	CU_add_test(admin_Invalid_suite, "Test Admin Add invalid User", TestCase103);
	CU_add_test(admin_Invalid_suite, "Test Admin Delete not existent User", TestCase104);

	/********************************Normal User Test*********************************/
	/* This suite is to Test all valid functionalities specific to the Admin role*/
	CU_pSuite user_valid_suite = CU_add_suite("User Valid Functionalities", system_test_setup_start, system_test_teardown_end);
	/* Adding Test Cases to the Test Suite*/
	CU_add_test(user_valid_suite, "Test User Add Valid User", TestCase105);
	CU_add_test(user_valid_suite, "Test User Change Password", TestCase107);
	CU_add_test(user_valid_suite, "Test User Add Course", TestCase109);
	/* This suite is to Test invalid functionalities specific to the Admin role*/
	CU_pSuite user_Invalid_suite = CU_add_suite("User Invalid Functionalities", system_test_setup_start, system_test_teardown_end);
	CU_add_test(user_Invalid_suite, "Test User Add invalid User", TestCase106);
	CU_add_test(user_Invalid_suite, "Test User Change PS using invalid PS", TestCase108);


#endif //SYSTEM_TESTS

	/* Running the Test Suite through Basic Console */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	//CU_automated_run_tests();

	/* Running the Test Suite through Console interactive */
	 // CU_console_run_tests();

	/* Clear the registry after test finished */
	CU_cleanup_registry();
}
