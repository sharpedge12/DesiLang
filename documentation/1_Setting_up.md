# DesiLang Setup Guide

This guide will help you set up **DesiLang** on your machine and get you started with writing and running programs.

## Prerequisites

Before installing **DesiLang**, ensure you have the following:

1. **C++ Compiler (GCC or Clang)**:

   - **Windows**: Install [MSYS2](https://www.msys2.org/) or [MinGW](http://www.mingw.org/).
   - **Linux**: GCC/Clang should already be available. Install with `sudo apt install build-essential` (for Ubuntu/Debian).
   - **macOS**: Install Xcode command-line tools via `xcode-select --install`.

2. **Make**:

   - **Windows**: Install **Make** using MSYS2, or via a package manager like [Chocolatey](https://chocolatey.org/) (`choco install make`).
   - **Linux**: Install `make` using:

     ```bash
     sudo apt install make
     ```

   - **macOS**: Install **Make** with Homebrew by running:

     ```bash
     brew install make
     ```

3. **Git**:
   - Install **Git** from [here](https://git-scm.com/).

---

## _Setup Instructions_

1. **Clone the DesiLang repository**:

   Open a terminal or command prompt and run the following command to clone the repository:

   ```bash
   git clone https://github.com/sharpedge12/DesiLang
   ```

2. **Navigate to the DesiLang directory**:

   After cloning, go to the DesiLang folder:

   ```bash
   cd DesiLang
   ```

3. **Compile using Make**:

   Once you're inside the DesiLang folder, run the following command to compile the project:

   ```bash
   make
   ```

   This will build the DesiLang compiler.

4. **Running DesiLang**:

   After compiling, you can use desilang.exe from the command prompt. To run a DesiLang program, use:

   ```bash
   desilang.exe yourprogram.desi
   ```

   Replace your_program.dsl with the path to your DesiLang file.

   For seeing help and other options , use :

   ```bash
   desilang.exe -h
   ```

   [Index](index.md) | [next: Basic Concepts ->](2_Basic_Concepts.md)

# DesiLang सेटअप गाइड

यह गाइड आपको **DesiLang** को अपने मशीन पर सेटअप करने और प्रोग्राम लिखने और चलाने में मदद करेगा।

## पूर्व शर्तें

**DesiLang** इंस्टॉल करने से पहले यह सुनिश्चित करें कि आपके पास निम्नलिखित हैं:

1. **C++ Compiler (GCC या Clang)**:

   - **Windows**: [MSYS2](https://www.msys2.org/) या [MinGW](http://www.mingw.org/) इंस्टॉल करें।
   - **Linux**: GCC/Clang पहले से उपलब्ध होना चाहिए। `sudo apt install build-essential` कमांड से इंस्टॉल करें (Ubuntu/Debian के लिए)।
   - **macOS**: Xcode कमांड-लाइन टूल्स इंस्टॉल करें `xcode-select --install` कमांड से।

2. **Make**:

   - **Windows**: **Make** को MSYS2 के जरिए इंस्टॉल करें, या [Chocolatey](https://chocolatey.org/) जैसे पैकेज मैनेजर से (`choco install make`)।
   - **Linux**: `make` को इंस्टॉल करने के लिए:

     ```bash
     sudo apt install make
     ```

   - **macOS**: Homebrew के माध्यम से **Make** इंस्टॉल करें:

     ```bash
     brew install make
     ```

3. **Git**:
   - **Git** को [यहाँ](https://git-scm.com/) से इंस्टॉल करें।

---

## _सेटअप निर्देश_

1. **DesiLang रिपॉजिटरी को क्लोन करें**:

   एक टर्मिनल या कमांड प्रॉम्प्ट खोलें और निम्नलिखित कमांड चलाकर रिपॉजिटरी को क्लोन करें:

   ```bash
   git clone https://github.com/sharpedge12/DesiLang
   ```

2. **DesiLang डायरेक्टरी में जाएं**:

   क्लोन करने के बाद, DesiLang फ़ोल्डर में जाएं:

   ```bash
   cd DesiLang
   ```

3. **Make का उपयोग करके कम्पाइल करें**:

   एक बार जब आप DesiLang फ़ोल्डर में पहुंच जाएं, तो प्रोजेक्ट को कम्पाइल करने के लिए निम्नलिखित कमांड चलाएं:

   ```bash
   make
   ```

   यह DesiLang कंपाइलर को बनाएगा।

4. **DesiLang चलाना**:

   कम्पाइल करने के बाद, आप कमांड प्रॉम्प्ट से desilang.exe का उपयोग कर सकते हैं। एक DesiLang प्रोग्राम चलाने के लिए:

   ```bash
   desilang.exe yourprogram.desi
   ```

   यहाँ your_program.dsl को अपने DesiLang फ़ाइल के पथ से बदलें।

   सहायता और अन्य विकल्प देखने के लिए, उपयोग करें:

   ```bash
   desilang.exe -h
   ```

   [Index](index.md) | [next: Basic Concepts ->](2_Basic_Concepts.md)
