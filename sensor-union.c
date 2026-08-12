#include <stdio.h>
#include <string.h>

typedef union
{
    int intValue;
    float floatValue;
} SensorReading;

typedef struct
{
    int sensorID;
    char sensorName[50];
    int readingType;
    SensorReading reading;
} Sensor;

/* Pass union by value */
void displaySensorValue(SensorReading reading, int type)
{
    if (type == 1)
        printf("Reading : %d\n", reading.intValue);
    else
        printf("Reading : %.2f\n", reading.floatValue);
}

/* Read sensor details */
void readSensor(Sensor *sensor)
{
    int choice;

    printf("Enter Sensor ID : ");
    scanf("%d", &sensor->sensorID);

    printf("Enter Sensor Name : ");
    scanf("%49s", sensor->sensorName);

    printf("\nChoose Reading Type\n");
    printf("1. Integer\n");
    printf("2. Float\n");
    printf("Choice : ");
    scanf("%d", &choice);

    sensor->readingType = choice;

    if (choice == 1)
    {
        printf("\nEnter Integer Reading : ");
        scanf("%d", &sensor->reading.intValue);
    }
    else if (choice == 2)
    {
        printf("\nEnter Float Reading : ");
        scanf("%f", &sensor->reading.floatValue);
    }
    else
    {
        printf("Invalid choice\n");
        sensor->readingType = 1;
        sensor->reading.intValue = 0;
    }
}

/* Display sensor information */
void displaySensor(Sensor *sensor)
{
    printf("\nSensor Details\n");
    printf("ID : %d\n", sensor->sensorID);
    printf("Name : %s\n", sensor->sensorName);

    displaySensorValue(sensor->reading, sensor->readingType);
}

/* Update sensor value - union passed by pointer */
void updateSensor(SensorReading *reading, int type)
{
    if (type == 1)
    {
        printf("Enter Updated Integer Value : ");
        scanf("%d", &reading->intValue);

        printf("Updated Value : %d\n", reading->intValue);
    }
    else
    {
        printf("Enter Updated Float Value : ");
        scanf("%f", &reading->floatValue);

        printf("Updated Value : %.2f\n", reading->floatValue);
    }
}

/* Compare two sensors */
void compareSensor(Sensor *s1, Sensor *s2)
{
    if (s1->readingType != s2->readingType)
    {
        printf("\nCannot compare sensors with different reading types.\n");
        return;
    }

    if (s1->readingType == 1)
    {
        if (s1->reading.intValue > s2->reading.intValue)
            printf("\nSensor %d has the higher reading.\n", s1->sensorID);
        else if (s1->reading.intValue < s2->reading.intValue)
            printf("\nSensor %d has the higher reading.\n", s2->sensorID);
        else
            printf("\nBoth sensors have equal readings.\n");
    }
    else
    {
        if (s1->reading.floatValue > s2->reading.floatValue)
            printf("\nSensor %d has the higher reading.\n", s1->sensorID);
        else if (s1->reading.floatValue < s2->reading.floatValue)
            printf("\nSensor %d has the higher reading.\n", s2->sensorID);
        else
            printf("\nBoth sensors have equal readings.\n");
    }
}

/* Reset sensor */
void resetSensor(Sensor *sensor)
{
    sensor->reading.intValue = 0;
    sensor->readingType = 1;

    printf("\nSensor %d has been reset.\n", sensor->sensorID);
}

int main()
{
    Sensor sensor1;
    Sensor sensor2;

    printf("Enter details for Sensor 1\n");
    readSensor(&sensor1);

    displaySensor(&sensor1);

    printf("\nUpdating Reading...\n");
    updateSensor(&sensor1.reading, sensor1.readingType);

    printf("\nEnter details for Sensor 2\n");
    readSensor(&sensor2);

    displaySensor(&sensor2);

    printf("\nComparing Sensors...\n");
    compareSensor(&sensor1, &sensor2);

    printf("\nResetting Sensor 1...\n");
    resetSensor(&sensor1);

    return 0;
}
