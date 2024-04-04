#include <iostream>
#include <unistd.h>
#include <thread>
#include <jni.h>
#include <dlfcn.h>
#include <link.h>
#include "BNM.cpp"
//The idea from first Il2Cpp Dumper called PokemonGoDumper
//https://github.com/Jumboperson/PokemonGoDumper/blob/master/main.c#L569

void *pLibRealUnity = 0;

typedef jint(JNICALL *CallJNI_OnLoad_t)(JavaVM *vm, void *reserved);

CallJNI_OnLoad_t RealJNIOnLoad = 0;

JNIEXPORT jint JNICALL CallJNIOL(JavaVM *vm, void *reserved) {
// LOGI("OnLoad called");
std::thread(hook_thread).detach();
if (!pLibRealUnity)
pLibRealUnity = dlopen("librealmain.so", RTLD_NOW);
if (!pLibRealUnity)
pLibRealUnity = dlopen("librealunity.so", RTLD_NOW);
if (!RealJNIOnLoad)
RealJNIOnLoad = reinterpret_cast<CallJNI_OnLoad_t>(dlsym(pLibRealUnity, "JNI_OnLoad"));
return RealJNIOnLoad(vm, reserved);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
JNIEnv *env;
vm->GetEnv((void **) &env, JNI_VERSION_1_6);
BNM::TryForceLoadIl2CppByPath(env);
// LOGI("Initialize JNI");
return CallJNIOL(vm, reserved);
}
