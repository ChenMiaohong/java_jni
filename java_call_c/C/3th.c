#include<stdio.h>
#include<jni.h>
#if 0
typedef struct{
    char *name;//java
    char *signature;//JNI
    void *fnPtr;//
}JNINativeMethod;
#endif //
jstring c_hello(JNIEnv *env, jclass cls, jstring str);
static const JNINativeMethod methods[] = {
    {"hello", "(Ljava/lang/String;)Ljava/lang/String;", (void *)c_hello},
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
    cls = (*env)->FindClass(env, "JNI2");
    if (cls == NULL)
    {
        return JNI_ERR;
    }
    if((*env)->RegisterNatives(env,cls,methods,1)<0)
        return JNI_ERR;
    return JNI_VERSION_1_4;
}
jstring c_hello(JNIEnv * env, jclass cls, jstring str) 
{
   const jbyte *cstr;
   cstr = (*env)->GetStringUTFChars(env,str,NULL);
   if(cstr==NULL)
   {
	return NULL;
   }
    printf("hello world,c is  %s\n",cstr);
    (*env)->ReleaseStringUTFChars(env,str,cstr);
    return (*env)->NewStringUTF(env,"from c");
}

