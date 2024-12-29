# Control Flow

In DesiLang, control flow is done with symbols instead of keywords. There are two symbols used for control flow, `?` and `@`. `|` is used in conjunction with one of them.

## If/Then

`?` is used for ifs. You may be familiar with the ternary operator in C like languages. In DesiLang `?` can be used in much the same way (the only difference is `|` is used instead of `:`), but `?` is also used for all if statements with `|` being the 'else' operator. The body of an if statement is usually enclosed in parentheses, but this is optional if there is only one line in it. For 'else if', follow an else with another if statement. Here is an example:

```

a: sach
b: 8

a ?
print: 1

b<4 ?
print: 2
|
print: 3

a && b<7 ?
(
print: 4
)
| b=8 ?
(
print: 5
)|(
print: 6
)

```

The output of that code is

```

> 1
> 3
> 5

```

## loops

`@` is the loop operator. It is used for while and for loops.

A simple while loop is below:

```

i: 8

i>=0 @
(
print: i
i: i-1
)

```

Like if, the perenthesis would be optional if there was only one statement in the body.

For loops are are based on C for loops, in that the header consits of 3 expressions, the first sets it up, the second checks if to continue each iteration and the third increments a vairable. The expressions are seporated with `|`. Here is an example:

```

i: 0 | i<12 | i: i+1 @
(
print: i
)

```

The output of this is the numbers 0-11.

[index](index.md) | [next: Shabd and Lelo ->](4_Shabd_And_Lelo.md)

# नियंत्रण प्रवाह

DesiLang में, नियंत्रण प्रवाह को कीवर्ड्स के बजाय प्रतीकों के साथ किया जाता है। नियंत्रण प्रवाह के लिए दो प्रतीकों का उपयोग किया जाता है, `?` और `@`। `|` को इन दोनों के साथ मिलाकर उपयोग किया जाता है।

## If/Then

`?` का उपयोग `if` के लिए किया जाता है। आप C जैसे भाषाओं में टर्नरी ऑपरेटर से परिचित होंगे। DesiLang में `?` का उपयोग उसी तरह किया जा सकता है (एकमात्र अंतर यह है कि `:` के बजाय `|` का उपयोग किया जाता है), लेकिन `?` का उपयोग सभी `if` स्टेटमेंट्स के लिए किया जाता है, जिसमें `|` को 'else' ऑपरेटर के रूप में उपयोग किया जाता है। एक `if` स्टेटमेंट के शरीर को आमतौर पर कोष्ठक में लपेटा जाता है, लेकिन अगर इसमें केवल एक पंक्ति है तो यह वैकल्पिक होता है। 'else if' के लिए, एक `else` के बाद एक और `if` स्टेटमेंट आता है। यहां एक उदाहरण है:

```

a: sach
b: 8

a ?
 print: 1

b<4 ?
 print: 2
|
 print: 3

a && b<7 ?
(
 print: 4
)
| b=8 ?
(
 print: 5
)|(
 print: 6
)

```

इस कोड का आउटपुट होगा:

```

> 1
> 3
> 5

```

## लूप्स (Loops)

`@` लूप ऑपरेटर है। इसका उपयोग `while` और `for` लूप्स के लिए किया जाता है।

यहां एक साधारण `while` लूप है:

```

i: 8

i>=0 @
(
 print: i
 i: i-1
)

```

जैसे `if`, अगर शरीर में केवल एक बयान हो तो कोष्ठक वैकल्पिक होते हैं।

`for` लूप्स C के `for` लूप्स पर आधारित होते हैं, जिसमें हेडर में 3 अभिव्यक्तियाँ होती हैं: पहली इसे सेट करती है, दूसरी प्रत्येक पुनरावृत्ति को जारी रखने की जांच करती है, और तीसरी किसी चर को बढ़ाती है। अभिव्यक्तियाँ `|` से अलग होती हैं। यहां एक उदाहरण है:

```

i: 0 | i<12 | i: i+1 @
(
 print: i
)

```

इसका आउटपुट 0 से 11 तक के नंबर होंगे।

[index](index.md) | [अगला: Shabd और Lelo ->](4_Shabd_And_Lelo.md)
