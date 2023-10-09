// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("osaclient");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("osaclient")
//      }
//    }

#include <android/log.h>
#include <jni.h>
#include <string>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/random.h>


//Is called from app/src/main/java/com/example/osaclient/MainActivity.kt
 extern "C" jstring JNICALL
Java_com_example_osaclient_MainActivity_testFunctionality(JNIEnv *env, jobject thiz) {
    std::string str;
    { //some random wolfssl code to test if it works
         WC_RNG rng;
         int sz = 32;
         unsigned char block[sz];
         int ret = wc_InitRng(&rng);
         if (ret != 0) {
             throw new std::runtime_error("init of rng failed");
         }
         ret = wc_RNG_GenerateBlock(&rng, block, sz);
         if (ret != 0) {
             throw new std::runtime_error("generating block failed");
         }
         wc_FreeRng(&rng);
         str = std::string(reinterpret_cast< char const * >(block), sz);
     }

 return env->NewStringUTF(str.c_str());

}

