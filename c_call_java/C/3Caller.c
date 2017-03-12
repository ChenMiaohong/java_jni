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
    jmethodID cid; 
    jobject jobj;
    jstring jstr;
    jfieldID nameID;
    jfieldID ageID;
    int ret = 0;   
    int r;
    /*create java virtual machine*/
    if(create_vm(&jvm,&env))//return value is not 0 is fail
    {
	printf("can not create jvm\n");
	return -1;
    }
    /*get class*/
    cls = (*env)->FindClass(env,"Hello3");
    if(cls==NULL)
    {
	printf("can not find hello class\n");
	ret = -1;
	goto destroy;
    }
    /*create object*/
    /*3.1 get construct method */
    /*3.2 create parameters*/
    /*3.3 NewObject*/
    /*Get method ID for the String construct*/
    cid = (*env)->GetMethodID(env,cls,"<init>","()V");
    if(cid==NULL)
    {
	ret = -1;
	printf("can not get construct method\n");
	goto destroy;
    }
     jobj = (*env)->NewObject(env,cls,cid);
     if(jobj==NULL)
    {
        printf("can not create the object\n");
        ret = -1;
        goto destroy;
    }
    /*
    *get/set filed 
    *1.get filed id
    *2.get/set filed
    */
    nameID = (*env)->GetFieldID(env,cls,"name","Ljava/lang/String;");
    if(nameID==NULL)
    {
        ret = -1;
        printf("can not get the field name\n");
        goto destroy;
    }
    jstr = (*env)->NewStringUTF(env,"chenswpu");
    (*env)->SetObjectField(env,jobj,nameID,jstr);
    ageID = (*env)->GetFieldID(env,cls,"age","I");
    if(ageID==NULL)
    {
        ret = -1;
        printf("cna not get field age");
	goto destroy;
    
    }
    (*env)->SetIntField(env,jobj,ageID,10);
    /*call method
    *4.1 get method 
    *4.2 create method 
    *4.3 call method
    */
    mid = (*env)->GetMethodID(env,cls,"Sayhello","(Ljava/lang/String;)I");
    if(mid ==NULL){
	ret = -1;
	printf("can not get the method\n");
	goto destroy;
    }
    jstr = (*env)->NewStringUTF(env,"chnswpuiot");
    r = (*env)->CallIntMethod(env,jobj,mid,jstr);
    printf("r is %d\n",r);
destroy:
    (*jvm)->DestroyJavaVM(jvm);
    return ret;
}
