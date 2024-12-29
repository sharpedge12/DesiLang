# Transpiling to C++

Until now, you have been using the default interpreter to run your DesiLang code. However, DesiLang also allows you to transpile your code to C++. In this section, we will explore how to do that and discuss the pros and cons of transpiling.

## Interpreting, Compiling, and Transpiling Explained

### Compiling:

Compiling is the process of converting one programming language into another. Typically, it means translating a high-level language like C, C++, or Rust into machine code, which can then be executed directly by a computer's hardware. This process produces fast, efficient executable programs.

### Interpreting:

In contrast to compiling, interpreting involves reading and executing a program line by line. Languages like Python, Ruby, and JavaScript are commonly interpreted. Interpreting offers flexibility, but it usually results in slower execution speeds compared to compiled languages.

### Transpiling:

Transpiling, short for "source-to-source compiling," is a specialized form of compilation where code is converted between two languages of similar complexity. For example, you might transpile modern JavaScript code into an older version of JavaScript to ensure compatibility with older browsers.

In the case of DesiLang, transpiling converts DesiLang code into C++ code, which can then be compiled and executed. This offers significant performance improvements over using the interpreter.

## DesiLang and Transpiling

DesiLang was initially designed with compiled languages in mind. While the interpreter remains the default method of execution, you now have the option to transpile DesiLang code to C++ for faster performance.

The interpreter is still the go-to option because it doesn’t require writing files to disk or using an external compiler. Additionally, there are certain cases where transpiling may not work as expected. However, for most cases, transpiling to C++ will yield much better performance for your programs.

## How to Use the DesiLang Transpiler

There are three command-line options that enable transpiling in DesiLang:

- `-cpp`: This option tells DesiLang to transpile the source code to C++.
- `-bin`: This option tells DesiLang to compile the transpiled C++ code into a binary executable.
- `-e`: This option, when used, will execute the program after transpiling, rather than just saving the output files.

You can combine these options in various ways. If any of these options are used, DesiLang will transpile the code instead of interpreting it.

### Example Usage:

1. `-cpp path/to/file.cpp`: Save the transpiled C++ source code to the specified path.
2. `-bin path/to/executable`: Compile the C++ code into a binary executable and save it to the specified path.
3. `-e`: Execute the transpiled program immediately after generating the C++ code and binary.

If you don't specify paths for the C++ or binary files, the transpiler will save them as temporary files in your current directory, which will be deleted automatically after execution.

### Important Notes:

- To compile a binary and execute it, you must have the GCC compiler installed on your system.
- Using the `-e` option will automatically execute the program after transpiling. All other arguments must appear before `-e`.

## Conclusion

Transpiling DesiLang code to C++ gives you the advantage of faster execution compared to using the interpreter. However, the interpreter remains the default due to its simplicity and flexibility, as it doesn't require external tools or file handling. For projects where performance is crucial, transpiling to C++ can provide a significant speed boost.

[index](index.md)

# C++ में ट्रांसपाइल करना

अब तक, आपने डेसीलैंग को चलाने के लिए डिफ़ॉल्ट इंटरप्रेटर का उपयोग किया है। हालांकि, डेसीलैंग आपको अपने कोड को C++ में ट्रांसपाइल करने की भी अनुमति देता है। इस खंड में, हम इसे कैसे करना है और ट्रांसपाइलिंग के फायदे और नुकसान पर चर्चा करेंगे।

## इंटरप्रेटिंग, कम्पाइलींग, और ट्रांसपाइलिंग समझाया

### कम्पाइलींग:

कम्पाइलींग एक प्रोग्रामिंग भाषा को दूसरी भाषा में बदलने की प्रक्रिया है। सामान्यतः इसका मतलब है एक उच्च-स्तरीय भाषा जैसे C, C++, या Rust को मशीन कोड में बदलना, जिसे फिर सीधे कंप्यूटर की हार्डवेयर द्वारा निष्पादित किया जा सकता है। यह प्रक्रिया तेज़ और प्रभावी निष्पादन करने वाले प्रोग्राम्स उत्पन्न करती है।

### इंटरप्रेटिंग:

कम्पाइलींग के विपरीत, इंटरप्रेटिंग में एक प्रोग्राम को लाइन दर लाइन पढ़कर और निष्पादित किया जाता है। Python, Ruby, और JavaScript जैसी भाषाएँ सामान्यतः इंटरप्रेटेड होती हैं। इंटरप्रेटिंग लचीलापन प्रदान करता है, लेकिन यह आमतौर पर कम्पाइलींग की तुलना में धीमी निष्पादन गति प्रदान करता है।

### ट्रांसपाइलिंग:

ट्रांसपाइलिंग, "सोर्स-टू-सोर्स कम्पाइलींग" का संक्षिप्त रूप है, जो एक विशेष प्रकार का कम्पाइलींग है जिसमें कोड को समान जटिलता वाली दो भाषाओं के बीच परिवर्तित किया जाता है। उदाहरण के लिए, आप आधुनिक JavaScript को एक पुराने संस्करण में ट्रांसपाइल कर सकते हैं ताकि यह पुराने ब्राउज़रों के साथ संगत हो सके।

डेसीलैंग के मामले में, ट्रांसपाइलिंग डेसीलैंग कोड को C++ कोड में परिवर्तित करता है, जिसे फिर से कम्पाइल और निष्पादित किया जा सकता है। इससे इंटरप्रेटर का उपयोग करने की तुलना में महत्वपूर्ण प्रदर्शन सुधार मिलता है।

## डेसीलैंग और ट्रांसपाइलिंग

डेसीलैंग को शुरू से ही संकलित भाषाओं के संदर्भ में डिजाइन किया गया था। जबकि इंटरप्रेटर अभी भी निष्पादन का डिफ़ॉल्ट तरीका है, अब आपके पास डेसीलैंग कोड को C++ में ट्रांसपाइल करने का विकल्प है ताकि आप बेहतर प्रदर्शन प्राप्त कर सकें।

इंटरप्रेटर अभी भी प्राथमिक विकल्प है क्योंकि इसे डिस्क पर फ़ाइलें लिखने की आवश्यकता नहीं होती है और न ही किसी बाहरी कम्पाइलर की आवश्यकता होती है। इसके अतिरिक्त, कुछ मामलों में ट्रांसपाइलिंग अपेक्षित रूप से काम नहीं कर सकती है। हालांकि, अधिकांश मामलों में, C++ में ट्रांसपाइलिंग आपके प्रोग्राम्स के लिए बेहतर प्रदर्शन प्रदान करेगा।

## डेसीलैंग ट्रांसपाइलर का उपयोग कैसे करें

डेसीलैंग में ट्रांसपाइलिंग को सक्षम करने के लिए तीन कमांड-लाइन विकल्प हैं:

- `-cpp`: यह विकल्प डेसीलैंग को सोर्स कोड को C++ में ट्रांसपाइल करने के लिए कहता है।
- `-bin`: यह विकल्प डेसीलैंग को ट्रांसपाइल किए गए C++ कोड को बाइनरी निष्पादन योग्य में संकलित करने के लिए कहता है।
- `-e`: यह विकल्प, जब इस्तेमाल किया जाता है, ट्रांसपाइलिंग के बाद प्रोग्राम को निष्पादित करेगा, केवल आउटपुट फाइलें बचाने के बजाय।

आप इन विकल्पों का विभिन्न तरीकों से संयोजन कर सकते हैं। यदि इनमें से कोई भी विकल्प प्रयोग में है, तो डेसीलैंग कोड को इंटरप्रेट करने के बजाय ट्रांसपाइल करेगा।

### उदाहरण उपयोग:

1. `-cpp path/to/file.cpp`: ट्रांसपाइल किए गए C++ सोर्स कोड को निर्दिष्ट पथ पर सहेजें।
2. `-bin path/to/executable`: C++ कोड को बाइनरी निष्पादन योग्य में संकलित करें और इसे निर्दिष्ट पथ पर सहेजें।
3. `-e`: ट्रांसपाइल किए गए प्रोग्राम को तुरंत निष्पादित करें, C++ कोड और बाइनरी बनाने के बाद।

यदि आप C++ या बाइनरी फ़ाइलों के लिए पथ निर्दिष्ट नहीं करते हैं, तो ट्रांसपाइलर उन्हें आपके वर्तमान डायरेक्टरी में अस्थायी फ़ाइलों के रूप में सहेजेगा, जो निष्पादन के बाद स्वचालित रूप से हटा दी जाएंगी।

### महत्वपूर्ण नोट्स:

- बाइनरी को संकलित करने और उसे निष्पादित करने के लिए, आपको अपने सिस्टम पर GCC कम्पाइलर इंस्टॉल करना होगा।
- `-e` विकल्प का उपयोग करने पर प्रोग्राम को ट्रांसपाइलिंग के बाद स्वचालित रूप से निष्पादित किया जाएगा। सभी अन्य विकल्पों को `-e` से पहले रखा जाना चाहिए।

## निष्कर्ष

डेसीलैंग को C++ में ट्रांसपाइल करने से आपको इंटरप्रेटर की तुलना में तेज़ निष्पादन का लाभ मिलता है। हालांकि, इंटरप्रेटर को डिफ़ॉल्ट रखा गया है क्योंकि यह सरलता और लचीलापन प्रदान करता है, क्योंकि इसे बाहरी उपकरणों या फ़ाइल प्रबंधन की आवश्यकता नहीं होती है। उन प्रोजेक्ट्स के लिए जहाँ प्रदर्शन महत्वपूर्ण है, C++ में ट्रांसपाइलिंग से महत्वपूर्ण गति वृद्धि हो सकती है।

[index](index.md)
