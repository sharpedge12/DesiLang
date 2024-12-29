## Functions

Functions must currently be declared as constants. In the future, non constant functions (aka lambda expressions) will be possible. The types a function takes and returns must be explicity stated in the header. A function header looks like this `{leftInput}.{rightInput} -> {returnType}`. The header should be followed by a colon and a perenthesis enclosed list of statements.

### Input and Output

The left input and return type can be omitted, in wich case they are `Void`. If you want the right input to be `Void`, simply leave the {} empty. Right input is the type of input you are already used to. Left input is a concept that is somewhat unique to DesiLang. It is just like right input, except that you call the function with `input.function` instead of `function: input`. A function can take both left and right input. The right input is named `in` and the left is named `me`. There is currently no return syntax in DesiLang, instead return value is the last expression in the function.

### Examples

```

# declaring functions (can be done above or below calling them)

addOne :: {ank} -> {ank}:
(
a: in+1
a
)

printNumbers :: {val1: dashamlav, val2: dashamlav}:
(
print: in.val1
print: in.val2
)

leftInput :: {ank}.{} -> {shabd}:(
print: me
"return str"
)

noArgs :: {}: (
print: "Hello"
)

# calling functions

print: addOne: 8

printNumbers: 7, 12

print: 8.leftInput

noArgs
```

The result of this code is

```
9
7.0
12.3
8
return str
Hello
```

## Overloading

You can make multiple functions with the same name as long as they take different types. This is called overloading.

[index](index.md) | [next: Kuchbhi ->](6_Kuchbhi.md)

## फ़ंक्शन्स

वर्तमान में, फ़ंक्शन्स को स्थिरांक के रूप में घोषित किया जाना चाहिए। भविष्य में, गैर-स्थिरांक फ़ंक्शन्स (जिन्हें लैम्ब्डा एक्सप्रेशन्स कहा जाता है) संभव होंगे। एक फ़ंक्शन को जो इनपुट लेता है और जो रिटर्न करता है, उसे हेडर में स्पष्ट रूप से बताया जाना चाहिए। एक फ़ंक्शन का हेडर इस तरह दिखता है `{leftInput}.{rightInput} -> {returnType}`। हेडर के बाद एक कॉलन और एक परेन्थेसिस से घेरें गए स्टेटमेंट्स की सूची होती है।

### इनपुट और आउटपुट

बाएं इनपुट और रिटर्न टाइप को छोड़ा जा सकता है, इस स्थिति में वे `Void` होते हैं। अगर आप चाहते हैं कि दाहिने इनपुट को `Void` होना चाहिए, तो बस `{}` को खाली छोड़ दें। दाहिना इनपुट वही है जो आप पहले से जानते हैं। बायां इनपुट DesiLang में एक अद्वितीय अवधारणा है। यह दाहिने इनपुट की तरह ही है, बस आप फ़ंक्शन को `input.function` से कॉल करते हैं न कि `function: input` से। एक फ़ंक्शन दोनों बाएं और दाहिने इनपुट ले सकता है। दाहिने इनपुट को `in` कहा जाता है और बाएं को `me` कहा जाता है। वर्तमान में DesiLang में रिटर्न सिंटैक्स नहीं है, बल्कि रिटर्न वैल्यू फ़ंक्शन में अंतिम एक्सप्रेशन होता है।

### उदाहरण

```

# फ़ंक्शन्स को घोषित करना (इन्हें कॉल करने से ऊपर या नीचे किया जा सकता है)

addOne :: {ank} -> {ank}:
(
a: in+1
a
)

printNumbers :: {val1: dashamlav, val2: dashamlav}:
(
print: in.val1
print: in.val2
)

leftInput :: {ank}.{} -> {shabd}:(
print: me
"return str"
)

noArgs :: {}: (
print: "Hello"
)

# फ़ंक्शन्स को कॉल करना

print: addOne: 8

printNumbers: 7, 12

print: 8.leftInput

noArgs
```

इस कोड का परिणाम है

```
9
7.0
12.3
8
return str
Hello
```

## ओवरलोडिंग

आप एक ही नाम के कई फ़ंक्शन्स बना सकते हैं बशर्ते कि वे विभिन्न प्रकार के इनपुट लें। इसे ओवरलोडिंग कहा जाता है।

[index](index.md) | [अगला: Kuchbhi ->](6_Kuchbhi.md)
