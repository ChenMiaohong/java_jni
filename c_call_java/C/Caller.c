#include<stdio.h>
#include<jni.h>
/*gcc -I/usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -o Caller Caller.c -L /usr/lib/jvm/java-7-openjdk-amd64/jre/lib/amd64/server -ljvm*/
/*create java virtual machine*/
jint create_vm(JavaVM** jvm,JNIEnv** env) {    
    JavaVMInitArgs args;  
    JavaVMOption options[1];  
    args.version = JNI_VERSION_1_6;  
    args.nOptions = 1;  
    options[0].optionString = "-Djava.class.path=./";  
    args.options = options;  
    args.ignoreUnrecognized = JNI_FALSE;  
    return  JNI_CreateJavaVM(jvm, (void **)env, &args);  
        
    }  
int main(int argc,char **argv)
{
    JavaVM* jvm;
    JNIEnv* env;
    jclass cls;
    jmethodID mid; 
    int ret = 0;   
    /*create java virtual machine*/
    if(create_vm(&jvm,&env))//return value is not 0 is fail
    {
	printf("can not create jvm\n");
	return -1;
    }
    /*get class*/
    cls = (*env)->FindClass(env,"Hello");
    if(cls==NULL)
    {
	printf("can not find hello class\n");
	ret = -1;
	goto destroy;
    }

    /*create object*/


    /*call method
    *4.1 get method 
    *4.2 create method 
    *4.3 call method
    */
    mid = (*env)->GetStaticMethodID(env,cls,"main","([Ljava/lang/String;)V");
    if(mid ==NULL){
	ret = -1;
	printf("can not get the method\n");
	goto destroy;
    }
    (*env)->CallStaticVoidMethod(env,cls,mid,NULL);
destroy:
    (*jvm)->DestroyJavaVM(jvm);
    return ret;
}
