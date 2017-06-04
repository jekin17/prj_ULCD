#include "sdcard_HandlerTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "fatfs.h"




/* Function prototypes -------------------------------------------------------*/
void sdcard_memory_thread(void const * argument);


FATFS fileSystem;
FIL testFile;
uint8_t testBuffer[16] = "SD write success";
UINT testBytes;
FRESULT res;

osThreadId sdcardTaskHandle;


void sdcard_memory_thread(void const * argument)
{
	do
	{
		if(f_mount(&fileSystem, (const TCHAR*)SD_Path, 1) == FR_OK)
		{
			HAL_GPIO_WritePin(led_RED_GPIO_Port,led_RED_Pin,GPIO_PIN_SET);
			char path[13] = "testfile.txt";
			path[12] = '\0';
			res = f_open(&testFile, (const TCHAR*)path, FA_WRITE | FA_CREATE_ALWAYS);
			res = f_write(&testFile, testBuffer, 16, &testBytes);
			res = f_close(&testFile);
			HAL_GPIO_WritePin(led_RED_GPIO_Port,led_RED_Pin,GPIO_PIN_RESET);
		}
		osDelay(2000);
	}
	while(1);
}


/** Initialize the sdcardFileSystem (start its thread) */
void sdcard_memory_thread_init()
{
	osThreadDef(sdcard_memory_handler, sdcard_memory_thread, osPriorityNormal, 0, 1280);
	sdcardTaskHandle = osThreadCreate(osThread(sdcard_memory_handler), NULL);
}
