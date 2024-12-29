# kuchbhi

## The Problem

Sometimes explicitly declaring a type is inconvenient. You don't want a function to always take an ank, shabd or any other specific type. You just want it to take whatev. Thats why DesiLang has the kuchbhi type.

## How it Works

kuchbhi in DesiLang work very similar to templates and generics in other languages. You declare a function that takes a kuchbhi, and then the compiler makes different versions of that function for each type you try to send into it. Note that kuchbhi do not enable dynamic typing at runtime. You can not make a kuchbhi variable except as an argument to a function.

## Using kuchbhi

The syntax is amazingly simple. kuchbhi is just a type, so you can use it like so:

```

# take any type, convert it to a string and return it wrapped in parenthesis

putInPeren :: {kuchbhi} -> {kuchbhi}:
(
"(" + in.shabd + ")"
)

print: putInPeren: 8
print: putInPeren: sach
```

The output of this code is

```
(8)
(sach)
```

Note that all types you use this function with must have an overload of the .shabd function defined, else you'll get a compile time error.

## kuchbhi in Structs

kuchbhi can be used in structs. here is an example:

```

# define the struct

MykuchbhiStruct ::
{
foo: ank
bar: kuchbhi
}

# define the constructor

makeMykuchbhiStruct :: {a: ank, b: kuchbhi} -> {MykuchbhiStruct}:
(
in.a, in.b
)

# define the print function for makeMykuchbhiStruct

print :: {MykuchbhiStruct}:
(
print: in.foo.shabd + ", " + in.bar.shabd
)

# use the struct

a: makeMykuchbhiStruct: 8, 9.3
b: makeMykuchbhiStruct: 2, jhut

print: a
print: b
```

The output of this is

```
8, 9.3
2, jhut
```

[index](index.md) | [next: Transpiling to C++ ->](7_Transpiling_To_Cpp.md)

# कुछभी

## समस्या

कभी-कभी किसी प्रकार को स्पष्ट रूप से घोषित करना असुविधाजनक होता है। आप नहीं चाहते कि कोई फ़ंक्शन हमेशा एक `ank`, `shabd` या किसी अन्य विशिष्ट प्रकार को ही ले। आप चाहते हैं कि वह कुछ भी ले सके। यही कारण है कि DesiLang में `kuchbhi` प्रकार है।

## यह कैसे काम करता है

DesiLang में `kuchbhi` दूसरे भाषाओं में टेम्पलेट्स और जनरिक्स के समान काम करता है। आप एक फ़ंक्शन घोषित करते हैं जो `kuchbhi` लेता है, और फिर कंपाइलर उस फ़ंक्शन के विभिन्न संस्करण बनाता है हर प्रकार के लिए जिसे आप इसमें भेजते हैं। ध्यान दें कि `kuchbhi` रनटाइम पर डायनेमिक टाइपिंग को सक्षम नहीं करता है। आप `kuchbhi` वेरिएबल केवल एक फ़ंक्शन के आर्ग्युमेंट के रूप में ही बना सकते हैं।

## kuchbhi का उपयोग

सिंटैक्स बेहद सरल है। `kuchbhi` बस एक प्रकार है, तो आप इसे इस तरह उपयोग कर सकते हैं:

```

# किसी भी प्रकार को लें, उसे स्ट्रिंग में बदलें और उसे परेन्थेसिस में लपेट कर वापस करें

putInPeren :: {kuchbhi} -> {kuchbhi}:
(
"(" + in.shabd + ")"
)

print: putInPeren: 8
print: putInPeren: sach
```

इस कोड का परिणाम है:

```
(8)
(sach)
```

ध्यान दें कि आप जिस प्रकार के साथ इस फ़ंक्शन का उपयोग करते हैं, उस प्रकार में `.shabd` फ़ंक्शन का ओवरलोडेड संस्करण होना चाहिए, अन्यथा आपको कंपाइल टाइम एरर मिलेगा।

## kuchbhi को संरचनाओं में उपयोग करना

`kuchbhi` को संरचनाओं (structs) में उपयोग किया जा सकता है। यहां एक उदाहरण है:

```

# संरचना को परिभाषित करें

MykuchbhiStruct ::
{
foo: ank
bar: kuchbhi
}

# कंस्ट्रक्टर को परिभाषित करें

makeMykuchbhiStruct :: {a: ank, b: kuchbhi} -> {MykuchbhiStruct}:
(
in.a, in.b
)

# makeMykuchbhiStruct के लिए प्रिंट फ़ंक्शन परिभाषित करें

print :: {MykuchbhiStruct}:
(
print: in.foo.shabd + ", " + in.bar.shabd
)

# संरचना का उपयोग करें

a: makeMykuchbhiStruct: 8, 9.3
b: makeMykuchbhiStruct: 2, jhut

print: a
print: b
```

इसका परिणाम है:

```
8, 9.3
2, jhut
```

[index](index.md) | [अगला: C++ में ट्रांसपाइल करना ->](7_Transpiling_To_Cpp.md)
