#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <include/gfx.hpp>

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
 
    GFX::init();
    GFX::clear(0xFFFFCA82);
    GFX::drawRect(10,10,30,30,0xFF00FFFF);
    GFX::swapBuffers();

    SceCtrlData currentCtrlData;
    SceCtrlData oldCtrlData;

    setupCallbacks();
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    int x = 10;
    int y = 10;

    while(true){
        oldCtrlData = currentCtrlData;
        sceCtrlReadBufferPositive(&currentCtrlData, 1);
        if (oldCtrlData.Buttons != currentCtrlData.Buttons) {
        /* Your button check/controls code goes here */
            if(currentCtrlData.Buttons & PSP_CTRL_DOWN){
                x += 10;
                y += 10;
                GFX::clear(0xFFFFCA82);
                GFX::drawRect(10,y,30,30,0xFF00FFFF);
                GFX::swapBuffers();
            }
            if(currentCtrlData.Buttons & PSP_CTRL_UP){
                x -= 10;
                y -= 10;
                GFX::clear(0xFFFFCA82);
                GFX::drawRect(10,y,30,30,0xFF00FFFF);
                GFX::swapBuffers();
            }
        }
        
        sceDisplayWaitVblankStart();
    }
}