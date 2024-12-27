# sega-clock

A simple clock with sega font to run on a LilyGo T-Display S3.

Custom fonts can be created using the below steps.

- Install font locally on your system.
- Use the tool located here to create a new font project
    - https://processing.org/reference/text_.html
    - Tool -> Create -> Font and choose font/size
   
- Upload vlw file to - http://tomeko.net/online_tools/file_to_hex.php?lang=en

- copy hex into new font.h file with tags
```
      const uint8_t nameofFont[] PROGMEM = {<hex>};

```
