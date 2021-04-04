#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
PSP_MODULE_INFO("Tutorial",0,1,0);

//exit function
int exit_callback(int arg1,int arg2,void* common){
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp){
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback,NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks(){
    int thid = sceKernelCreateThread("update_thread",callbackThread,0x11,0xFA0,0,NULL);
    if(thid >=0 ){
        sceKernelStartThread(thid,0,NULL);
    }
}

auto main() -> int {
    pspDebugScreenInit();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    SceCtrlData ctrlData;

    while(true){
        sceCtrlReadBufferPositive(&ctrlData,1);
        if(ctrlData.Buttons & PSP_CTRL_UP)		    pspDebugScreenPrintf("Up"); 
        if(ctrlData.Buttons & PSP_CTRL_DOWN)	    pspDebugScreenPrintf("Down"); 
        if(ctrlData.Buttons & PSP_CTRL_RIGHT)	    pspDebugScreenPrintf("Right"); 
        if(ctrlData.Buttons & PSP_CTRL_LEFT)	    pspDebugScreenPrintf("Left"); 

        if(ctrlData.Buttons & PSP_CTRL_CROSS)	    pspDebugScreenPrintf("Cross"); 
        if(ctrlData.Buttons & PSP_CTRL_CIRCLE)	    pspDebugScreenPrintf("Circle"); 
        if(ctrlData.Buttons & PSP_CTRL_SQUARE)	    pspDebugScreenPrintf("Square"); 
        if(ctrlData.Buttons & PSP_CTRL_TRIANGLE)    pspDebugScreenPrintf("Triangle"); 

        if(ctrlData.Buttons & PSP_CTRL_RTRIGGER)	pspDebugScreenPrintf("R-Trigger");
        if(ctrlData.Buttons & PSP_CTRL_LTRIGGER)	pspDebugScreenPrintf("L-Trigger");
    }
}