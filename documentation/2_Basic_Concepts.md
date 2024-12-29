# Basic Concepts

Let's start with the classic "Hello World" program. It's very easy in DesiLang:

```
print: "Hello World!"
```

That's all you need in your file. No includes or boilerplate code of any sort. Just save that as a normal text file with the extension `.desi` and run it.

## Data Types

1. **ank**: `69` is an example of **ank**. It's basically an integer and is the same as `int` in C++. It can hold positive and negative whole numbers.

2. **dashamlav**: `12.89` is an example of **dashamlav**. It is the same as `double` in C++. It can hold positive and negative decimal numbers.

3. **bool**: `_sach_` is an example of **bool**. It is the same as `bool` in C++. It holds two values: either `_sach_` (true) or `_jhut_` (false).

4. **shabd**: `"hello"` is an example of **shabd**. It is the same as a `string` in C++. It is a series of letters, numbers, or other characters of any length. You create a string by surrounding text in double quotes.

## Operators

In general, operators in DesiLang work the same as in any other language. It has all the ones you would expect with a sensible order of operations. The following are the only major differences between operators in DesiLang and C-style languages:

- The assignment operator is `:` instead of `=`.
- The equality operator is `=` instead of `==`.

## Calling Functions

`print: 42` is an example of a function call. **print** is a standard function that prints what it is sent, followed by a newline. The `:` indicates that you want to send input to print, and whatever follows is the input.

Functions can only take input of the exact type they are supposed to take. Functions can, however, be overloaded. This means there are multiple functions with the same name that are differentiated by the type of their input.

`print` is an overloaded function, so you can also do `print: 42.1`, or even just `print`, and it will compile (the latter takes no input and will just print an empty line).

Functions can also take input from the left, but we will get to that later.

## Variables

A **variable** is a place where you can store a value. Every variable has a type, but types are deduced implicitly. To create, change, and use a variable, simply do the following:

```
myVarName: 88
myVarName: 12
print: myVarName
```

`myVarName` can be any series of letters, digits, and underscores, as long as it doesn't start with a number. Variable names are case-sensitive.

As you can see, creating a variable, setting a variable, and calling a function all look the same. This is a very important feature of the language, as it makes refactoring variables into calculations much easier.

## Tuples

A Tuple can be thought of as an ad-hoc data structure. To construct one, you simply combine several expressions with commas. The names of the elements of a tuple are `a`, `b`, `c`, etc. Elements can be accessed with the `.` operator. Here is an example:

```
myTuple: 6, 2.9, jhut
print: myTuple.c
print: myTuple.a
```

The output of this will be:

```
jhut
6
```

## Constants

A **constant** is a value that is determined at compile time. Constants are created with the constant assignment operator `::`. You can declare constants above or below where you use them. Trying to set a constant more than once will result in a compile-time error. Here is an example of a simple use of constants:

```
a :: 3
print: b
b :: a+c
c :: 2
```

This will compile correctly and print `5`.

## Comments

Comments are parts of your program that the compiler doesn't look at, so you can write notes and explanations. In DesiLang, single-line comments start with a `#`. Multi-line comments start with `//` and end with `\\`.

## Explicit Type Conversion

Sometimes, you might want to send a value to a variable or function of a different type. In the future, this will just work, but for now, you must convert it explicitly. To do this, call the target type's name like a function. For example:

```
myDub: 12.7
myDub: 32 # won't work because 32 is an Int
myDub: dashamlav: 32 # explicit conversion
```

[index](index.md) | [next: Control Flow ->](3_Control_Flow.md)

# मूल अवधारणाएँ

आइए हम क्लासिक "Hello World" प्रोग्राम से शुरू करें। DesiLang में यह बहुत आसान है:

```
print: "Hello World!"
```

बस इतना ही आपको अपनी फ़ाइल में चाहिए। कोई भी इंक्लूड या बायलरप्लेट कोड की जरूरत नहीं है। इसे एक सामान्य टेक्स्ट फ़ाइल के रूप में `.desi` एक्सटेंशन के साथ सहेजें और चलाएं।

## डेटा प्रकार

1. **ank**: `69` एक **ank** का उदाहरण है। यह बुनियादी रूप से एक पूर्णांक है और C++ में `int` जैसा है। यह सकारात्मक और नकारात्मक पूर्ण संख्याओं को पकड़ सकता है।

2. **dashamlav**: `12.89` एक **dashamlav** का उदाहरण है। यह C++ में `double` जैसा है। यह सकारात्मक और नकारात्मक दशमलव संख्याओं को पकड़ सकता है।

3. **bool**: `_sach_` एक **bool** का उदाहरण है। यह C++ में `bool` जैसा है। यह दो मानों में से एक हो सकता है: या तो `_sach_` (सच) या `_jhut_` (झूठ)।

4. **shabd**: `"hello"` एक **shabd** का उदाहरण है। यह C++ में `string` जैसा है। यह किसी भी लंबाई के अक्षरों, संख्याओं या अन्य वर्णों की एक श्रृंखला है। आप टेक्स्ट को डबल कोट्स में घेरकर एक शाब्दिक स्ट्रिंग बनाते हैं।

## ऑपरेटर

सामान्य तौर पर, DesiLang में ऑपरेटर अन्य भाषाओं की तरह ही काम करते हैं। इसमें वे सभी ऑपरेटर होते हैं जिनकी आप अपेक्षा करते हैं और संचालन का एक समझदार क्रम होता है। DesiLang और C-शैली की भाषाओं के बीच ऑपरेटरों में मुख्य अंतर निम्नलिखित हैं:

- असाइनमेंट ऑपरेटर `:` है, न कि `=`।
- समानता ऑपरेटर `=` है, न कि `==`।

## फ़ंक्शन कॉल करना

`print: 42` एक फ़ंक्शन कॉल का उदाहरण है। **print** एक मानक फ़ंक्शन है जो जो भी इसे भेजा जाता है, उसे प्रिंट करता है और फिर एक नई लाइन प्रिंट करता है। `:` यह संकेत देता है कि आप print को इनपुट भेजना चाहते हैं, और जो भी इसके बाद है वह इनपुट है।

फ़ंक्शंस केवल उसी प्रकार का इनपुट ले सकते हैं जो वे लेने के लिए डिज़ाइन किए गए हैं। हालांकि, फ़ंक्शंस को ओवरलोड किया जा सकता है। इसका मतलब है कि एक ही नाम के कई फ़ंक्शंस हो सकते हैं जो उनके इनपुट के प्रकार से अलग-अलग होते हैं।

`print` एक ओवरलोडेड फ़ंक्शन है, इसलिए आप `print: 42.1` भी कर सकते हैं, या बस `print` भी कर सकते हैं, और यह संकलित हो जाएगा (यह कोई इनपुट नहीं लेता है और इसलिए बस एक खाली लाइन प्रिंट करेगा)।

फ़ंक्शंस बाएं से भी इनपुट ले सकते हैं, लेकिन हम इसके बारे में बाद में बात करेंगे।

## चर (Variables)

एक **चर** वह स्थान है जहाँ आप एक मान स्टोर कर सकते हैं। प्रत्येक चर का एक प्रकार होता है, लेकिन प्रकार स्वचालित रूप से निर्धारित होते हैं। एक चर बनाने, बदलने और उपयोग करने के लिए, बस निम्नलिखित करें:

```
myVarName: 88
myVarName: 12
print: myVarName
```

`myVarName` कोई भी अक्षरों, अंकों और अंडरस्कोरों की श्रृंखला हो सकता है, बशर्ते यह संख्या से शुरू न हो। चर के नाम बड़े और छोटे अक्षरों के लिए सेंसिटिव होते हैं।

जैसा कि आप देख सकते हैं, एक चर बनाना, सेट करना और एक फ़ंक्शन कॉल करना सभी समान दिखते हैं। यह भाषा की एक बहुत महत्वपूर्ण विशेषता है, क्योंकि इससे चर को गणनाओं में बदलने की प्रक्रिया आसान हो जाती है।

## ट्यूपल (Tuples)

एक ट्यूपल को एक अस्थायी डेटा संरचना के रूप में सोचा जा सकता है। एक ट्यूपल बनाने के लिए, आप बस कई अभिव्यक्तियों को अल्पविराम से जोड़ते हैं। एक ट्यूपल के तत्वों के नाम `a`, `b`, `c` आदि होते हैं। तत्वों को `.` ऑपरेटर से एक्सेस किया जा सकता है। यहाँ एक उदाहरण है:

```
myTuple: 6, 2.9, jhut
print: myTuple.c
print: myTuple.a
```

इसका आउटपुट होगा:

```
jhut
6
```

## स्थिरांक (Constants)

एक **स्थिरांक** वह मान होता है जो संकलन के समय निर्धारित होता है। स्थिरांकों को स्थिरांक असाइनमेंट ऑपरेटर `::` के साथ बनाया जाता है। आप स्थिरांकों को उनके उपयोग से ऊपर या नीचे घोषित कर सकते हैं। एक स्थिरांक को एक से अधिक बार सेट करने का प्रयास संकलन समय पर त्रुटि का कारण बनेगा। यहाँ स्थिरांकों का एक सरल उदाहरण है:

```
a :: 3
print: b
b :: a+c
c :: 2
```

This will compile correctly and print `5`.

## Comments

Comments are parts of your program that the compiler doesn't look at, so you can write notes and explanations. In DesiLang, single-line comments start with a `#`. Multi-line comments start with `//` and end with `\\`.

## Explicit Type Conversion

Sometimes, you might want to send a value to a variable or function of a different type. In the future, this will just work, but for now, you must convert it explicitly. To do this, call the target type's name like a function. For example:

```
myDub: 12.7
myDub: 32 # won't work because 32 is an Int
myDub: dashamlav: 32 # explicit conversion
```

[index](index.md) | [अगला: नियंत्रण प्रवाह ->](3_Control_Flow.md)
