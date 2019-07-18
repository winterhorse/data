#include <stdint.h>
#include <stdlib.h> //malloc
#include <global_errors.h>
#include <resource_manager_protected.h>

//*******************************************************
//Everything below is for a single 'set' type (i.e. APEX)
//*******************************************************

//fixed parameters(cannot change in a meaningful way with this implementation)
#define lInitInputArraySize 3
#define lNumSetTypes        1

//flexible parameters (depends on resource definition)
#define lMaxNameLength      20 //keep it the same for all strings for simplicity
#define lMaxNumSets         2  //max number of APEXs
#define lNumResTypes        3  //number of resource types within the APEX set
#define lMaxNumResources    6  //max number of resources taking all types into account (i.e. not max number per type)
#define lNumUserTypes       1  //number of user types
#define lMaxNumUsers        8  //max number of users taking all types into account (i.e. not max number per type)

 void*    gspResourceManagerBuffer = 0;
 uint32_t gsTypeIdArray[1 + lNumResTypes] = {0}; //contains one set ID followed by 'lNumResTypes' resource IDs (initialized by 'ResMgr_Set_Register')
 uint32_t gsUserTypeIdArray[lNumUserTypes] = {0};  //contains 'lNumUserTypes' user IDs (initialized by 'ResMgr_User_Type_Register')


 uint32_t ApexSetTypeId(){ return gsTypeIdArray[0]; }
 uint32_t APEX_ResTypeId(int32_t lResEnum){ return gsTypeIdArray[1 + lResEnum]; }
 uint32_t UserTypeId(int32_t lUserEnum){ return gsUserTypeIdArray[lUserEnum]; }
 
 uint32_t InitApexResReq(uint32_t lArray[4], uint32_t lApexId, uint32_t lResType, uint32_t lNumOrInstance)
 {
    lArray[0] = ApexSetTypeId();
    lArray[1] = lApexId;
    lArray[2] = APEX_ResTypeId(lResType);
    lArray[3] = lNumOrInstance;
    return 0;
 }

LIB_RESULT ResourceManagerInit_APEX(uint32_t lHwVersion)
{
   LIB_RESULT lRetVal = LIB_FAILURE;

   uint32_t const lInitInputArray[lInitInputArraySize][3] = { {lMaxNameLength, lNumSetTypes,  lMaxNumSets     },  //Set
                                                              {lMaxNameLength, lNumResTypes,  lMaxNumResources},  //Resource
                                                              {lMaxNameLength, lNumUserTypes, lMaxNumUsers    }}; //User

   const char lSetAndResNameArray[1 + lNumResTypes][lMaxNameLength+1] = { "APEX", //set name
                                                                          "APU",  //rest are resource names within the set
                                                                          "CU_32",
                                                                          "SMEM_64K"};
                                                                     
   const char lUserNameArray[lNumUserTypes][lMaxNameLength+1] = { "ACF" };
   
   uint32_t lMultiplicityArray[1 + lNumResTypes] = {0}; //will be initialized below depending on the HW configuration (321, 642, etc.)

   //determine the necessary buffer size
   uint32_t lReqBufSizeInBytes = 0;
   lRetVal = ResMgr_Initialize(0, 0, lInitInputArray, lInitInputArraySize, lMaxNumResources, &lReqBufSizeInBytes);
   
   if (LIB_SUCCESS == lRetVal && lReqBufSizeInBytes > 0)
   {
      gspResourceManagerBuffer = (void*)malloc(lReqBufSizeInBytes);
      
      if (gspResourceManagerBuffer != 0)
      {
         uint32_t lUsedSizeInBytes = 0;

         //initialization
         lRetVal = ResMgr_Initialize(gspResourceManagerBuffer, lReqBufSizeInBytes, lInitInputArray, lInitInputArraySize, lMaxNumResources, &lUsedSizeInBytes);
         
         if (LIB_SUCCESS == lRetVal)
         {
            switch (lHwVersion)
            {
            case 0x642:
               lMultiplicityArray[0] = 2; //APEX
               lMultiplicityArray[1] = 2; //APU
               lMultiplicityArray[2] = 2; //CU_32
               lMultiplicityArray[3] = 2; //SMEM_64K
               break;
            case 0x321:
               lMultiplicityArray[0] = 1; //APEX
               lMultiplicityArray[1] = 1; //APU
               lMultiplicityArray[2] = 1; //CU_32
               lMultiplicityArray[3] = 1; //SMEM_64K
               break;  
            default: //ERROR: unknown HW configuration detected
               lRetVal = LIB_FAILURE;
               break;
            }
            
            if (LIB_SUCCESS == lRetVal)
            {
               lRetVal = ResMgr_Set_Register((const char*)lSetAndResNameArray,
                                             lMaxNameLength,
                                             lMultiplicityArray,
                                             gsTypeIdArray,
                                             1 + lNumResTypes);
                                             
                if (LIB_SUCCESS == lRetVal)
                {
                   lRetVal = ResMgr_User_Type_Register((const char*)lUserNameArray,
                                                        lMaxNameLength,
                                                       gsUserTypeIdArray,
                                                        lNumUserTypes);
                }
            }                                          
         }
      }
   }
   
   return lRetVal;
}

LIB_RESULT ResourceManagerDeinit_APEX(uint32_t /*lHwVersion*/)
{
   LIB_RESULT lRetVal = LIB_SUCCESS;

   if (gspResourceManagerBuffer != 0)
   {
      lRetVal = ResMgr_Deinitialize();
      free(gspResourceManagerBuffer);
      gspResourceManagerBuffer = 0;
   }

   return lRetVal;
}





