#include<stdio.h>
#include<jni.h>
#if 0
typedef struct{
    char *name;//java
    char *signature;//JNI
    void *fnPtr;//
}JNINativeMethod;
#endif // 0
/*
**gcc -I/usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -fPIC -shared -o libnative.so native.c 
*/
jint c_hello(JNIEnv *env, jclass cls, jintArray arr);
static const JNINativeMethod methods[] = {
    {"hello", "([I)I", (void *)c_hello},
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
    cls = (*env)->FindClass(env, "JNI4");
    if (cls == NULL)
    {
        return JNI_ERR;
    }
    if((*env)->RegisterNatives(env,cls,methods,1)<0)
        return JNI_ERR;
    return JNI_VERSION_1_4;
}
jint c_hello(JNIEnv *env, jclass cls, jintArray arr)
{
    jint *carr;
    jint i,sum = 0;
    carr = (*env)->GetIntArrayElements(env,arr,NULL);
    if(carr==NULL)
	return 0;
    for(i=0;i<(*env)->GetArrayLength(env,arr);i++)
    {
 	sum = sum+carr[i];
    }
    (*env)->ReleaseIntArrayElements(env,arr,carr,0);
	return sum;
}
