This program implements a system that manages patients’ data in a hospital. 
 The hospital patient management system stores specific information in the form of health record to keep track of the patients’ data.
 The program reads the information from a file called “patients.txt” that should be on the following format: 
 Patient_Name#Gender#Date_of_admission#Date_of_birth #Illness#Address_(City)#Blood_type

**************************************************************
The system includes the following operations of an AVL tree:

• Read the file patients.txt and load the data (i.e., AVL Tree).

• Insert a new patient from user with all its associated data.

• Find a patient and give the user the option to update the information of the patient if found.

• List all patients in lexicographic order with their associated information.

• List all patients that have the same illness.

• Delete a patient from the system.

• Save all words in file “patients_hash.data”
**************************************************************

The program creates a Hash Table using the patients’ data of the previous step (names used as keys). 
 Open addressing methods was used for collision resolution 
the hash table implementa the following functions:

• Print hashed table (i.e., print the entire table to the screen including empty spots).

• Print out table size.

• Print out the used hash function.

• Insert a new record into the hash table.

• Search for a specific patient.

• Delete a specific record.

• Save hash table back to file.

