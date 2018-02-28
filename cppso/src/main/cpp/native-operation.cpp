//
// Created by glumes on 2018/2/28.
//

#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "NativeMethod"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)


extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeString(JNIEnv *env, jclass type) {

    // env 的 newXXX 方法可以生成各种类型
    jstring nativeString = env->NewStringUTF("hello native string");
    return nativeString;
}



extern "C"
JNIEXPORT jintArray JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeIntArray(JNIEnv *env, jclass type) {


    // TODO
    jsize arraySize = 10;

    jintArray intArray = env->NewIntArray(arraySize);

    for (int i = 0; i < arraySize; i++) {
//        intArray. = 0;
    }
    return intArray;

}


/**
 * 从 Native 层修改 Java Static 变量
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallStaticMethod(JNIEnv *env, jclass type) {

    // TODO
    jclass clazz;
    jfieldID fid;
    jint num;

    // 获得 JVM 中类的引用
    clazz = env->FindClass("com/glumes/cppso/callback/CallBackClass");
    if (clazz == NULL) {
        LOGD("can not find CallBackClass");
        return;
    }

    // 获得静态变量的属性 ID
    fid = env->GetStaticFieldID(clazz, "num", "I");
    if (fid == NULL) {
        LOGD("can not find field id");
        return;
    }

    // 获取静态变量 num 的值
    num = env->GetStaticIntField(clazz, fid);
    LOGD("CallBackClass int field value is %d", num);

    // 修改静态变量的值
    env->SetStaticIntField(clazz, fid, 88);

    // 删除属性引用
    env->DeleteLocalRef(clazz);
}




/**
 * 从 Native 层修改 Java 实例对象的属性值
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallInstanceMethod(JNIEnv *env, jclass type,
                                                                  jobject callback) {

    // TODO
    jclass clazz;
    jfieldID fid;
    jstring j_str;
    jstring j_newStr;
    const char *c_str = NULL;

    // 获得 JVM 中类的引用
    clazz = env->GetObjectClass(callback);

    if (clazz == NULL) {
        return;
    }

    // 获得类 的实例变量的属性 的引用 ID
    fid = env->GetFieldID(clazz, "str", "Ljava/lang/String;");
    if (fid == NULL) {
        return;
    }

    // 获得实例变量的值，转换为 jstring 类型
    j_str = (jstring) env->GetObjectField(callback, fid);


    // 将 unicode 编码的 java 字符串转换成 C 风格字符串
    c_str = env->GetStringUTFChars(j_str, NULL);

    if (c_str == NULL) {
        return;
    }

    env->ReleaseStringUTFChars(j_str, c_str);

    // 修改实例变量的值
    j_newStr = env->NewStringUTF("this is new string");

    if (j_newStr == NULL) {
        return;
    }

    env->SetObjectField(callback, fid, j_newStr);

    // 删除局部引用
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(j_str);
    env->DeleteLocalRef(j_newStr);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallSuperMethod(JNIEnv *env, jclass type) {

    // TODO

    LOGD("Call super method");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeTest(JNIEnv *env, jobject instance) {

    // TODO

}

