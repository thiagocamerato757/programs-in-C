#define MAX_PROGRAM_NAME_LENGTH 50
typedef struct{
    char name[MAX_PROGRAM_NAME_LENGTH];
    int priority;
    int initial_time;
    int duration;
    char type;
}program ; 