# Shabd and Lelo

In **DesiLang** , a shabd is a series of characters of any length. To make a shabd, simply surround some text in double quotes:

```
myShabd: "this is a shabd!!!"
```

## Operators and Functions

Like other types, there are various operators and functions that can be applied to shabds.

- `=` checks if two shabds are exactly the same.
- `+` combines two shabds.
- `shabdName.size` returns the length of that shabd.
- `68.ascii` will return a shabd one character long containing the ascii value of the ank.
- `shabdName.hissa: start, end` returns a substring.
- `84.shabd` will return a shabd with that number in base 10 (aka, normal). This can be done for ank, dashamlav and bool.

## String input

You can get a shabd as an input from the user. To do this, call `shabd.lelo`. This will block execution until they type sonething in and press enter, at which time the finction will return a string. If you want to give the user a prompt, call the function like this: `"please enter some input: ".lelo`.

[index](index.md) | [next: Functions ->](5_Functions.md)

# शबद और लेलो

**DesiLang** में, एक शबद किसी भी लंबाई के वर्णों की श्रृंखला होती है। एक शबद बनाने के लिए, बस कुछ टेक्स्ट को डबल कोट्स में घेरें:

```
myShabd: "यह एक शबद है!!!"
```

## ऑपरेटर्स और फंक्शंस

अन्य प्रकारों की तरह, शबद्स पर लागू करने के लिए विभिन्न ऑपरेटर्स और फंक्शंस होते हैं।

- `=` यह चेक करता है कि दो शबद बिल्कुल समान हैं या नहीं।
- `+` दो शबदों को जोड़ता है।
- `shabdName.size` उस शबद की लंबाई लौटाता है।
- `68.ascii` यह एक शबद लौटाएगा जिसमें अंक का ASCII मान होगा।
- `shabdName.hissa: start, end` एक उपशब्द (substring) लौटाएगा।
- `84.shabd` यह उस नंबर के साथ एक शबद लौटाएगा जो 10 आधारित संख्या (यानी, सामान्य) होगी। यह अंक, दशमलव और बूल के लिए भी किया जा सकता है।

## स्ट्रिंग इनपुट

आप उपयोगकर्ता से एक शबद के रूप में इनपुट ले सकते हैं। ऐसा करने के लिए, `shabd.lelo` कॉल करें। यह निष्पादन को रोक देगा जब तक कि उपयोगकर्ता कुछ टाइप करके एंटर नहीं दबा देता, जिसके बाद यह फंक्शन एक शबद लौटाएगा। अगर आप उपयोगकर्ता को एक संकेत देना चाहते हैं, तो यह फंक्शन इस प्रकार कॉल करें: `"कृपया कुछ इनपुट दर्ज करें: ".lelo`।

[index](index.md) | [अगला: Functions ->](5_Functions.md)
