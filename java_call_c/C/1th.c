#include<stdio.h>
#include<jni.h>
#if 0
typedef struct{
    char *name;//java
    char *signature;//JNI
    void *fnPtr;//
}JNINativeMethod;
#endif // 0
void c_hello(JNIEnv *env,jobject cls);
static const JNINativeMethod methods[] = {
    {"hello", "()V", (void *)c_hello},
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    JNIEnv *env;
    jclass cls;
    if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4))
    {
        return JNI_ERR; /* JNI version not supported */
    }
    cls = (*env)->FindClass(env, "JNI");
    if (cls == NULL)
    {
        return JNI_ERR;
    }
    if((*env)->RegisterNatives(env,cls,methods,1)<0)
        return JNI_ERR;
    return JNI_VERSION_1_4;
}


void c_hello(JNIEnv *env,jobject cls)
{
    printf("hello world\n");
}
