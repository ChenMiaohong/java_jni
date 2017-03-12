#include<stdio.h>
#include<jni.h>
#include<stdlib.h>
#if 0
typedef struct{
    char *name;//java
    char *signature;//JNI
    void *fnPtr;//
}JNINativeMethod;
#endif // 0
jintArray c_hello(JNIEnv *env, jclass cls, jintArray arr);
static const JNINativeMethod methods[] = {
    {"hello", "([I)[I", (void *)c_hello},
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
    cls = (*env)->FindClass(env, "JNI5");
    if (cls == NULL)
    {
        return JNI_ERR;
    }
    if((*env)->RegisterNatives(env,cls,methods,1)<0)
        return JNI_ERR;
    return JNI_VERSION_1_4;
}
jintArray c_hello(JNIEnv *env, jclass cls, jintArray arr)
{
    jint *carr;
    jint *oarr;
    jintArray rarr;
    jint i,n = 0;
    carr = (*env)->GetIntArrayElements(env,arr,NULL);
    if(carr==NULL)
        return 0;
    n =(*env)->GetArrayLength(env,arr);
    oarr = malloc(sizeof(jint)*n);
    if(oarr==NULL)
    {
	(*env)->ReleaseIntArrayElements(env,arr,carr,0);
	return 0;	
    }
    for(i=0;i<n;i++)
    {
        oarr [i] = carr[n-i-1];
    }
    (*env)->ReleaseIntArrayElements(env,arr,carr,0);
    rarr = (*env)->NewIntArray(env,n);
    if(rarr==NULL)
    {
        return 0;
    }
    (*env)->SetIntArrayRegion(env,rarr,0,n,oarr);
        free(oarr);
	return rarr;
    
}

