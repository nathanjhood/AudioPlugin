# AudioPlugin
JUCE Audio Plugin template (under construction)

Built-in features:
+ variable oversampling up to 16x
+ variable processing precision (floats or doubles)
+ dry/wet mix with optional latency compensation
+ master output gain for "wet" signal
+ local context bypass switch
+ master bypass switch
+ defeatable GUI (requires window close/re-open)
+ de-coupled processing and true-bypass of audio processors in a lock-free atomic structure

The plugin template consists of four containers, each dedicated to it's own role:

+ Processor - contains all the interactions between host and plugin
+ Editor - contains all graphical elements for user interaction
+ Parameters - contains all the control information to be accessed by the Editor and sent to the Wrapper
+ Wrapper - contains all the functions and audio processors of the plugin

Each of the above four containers is divided across two files;

+ .h (header) file - defines the functions of the container and exposes them as an interface
+ .cpp (source) file - defines the implementations of said functions of the container

All four containers are connected by an "Audio Processor Value Tree State" ("APVTS") object. The APVTS object is created and held in the Processor container, which then passes it forward to each of the other containers, before it is passed back to the Processor for further work.

The Parameters container comes first - our parameters are created by this container, including their various types (float value, boolean, multiple choice, etc), their min and max values, skew factors, and other details. These parameter objects (such as "volumeFader") are then passed into the APVTS, along with a reference name ID (such as "volumeID").

The Editor container is where our graphical elements, including knobs and sliders, are created and drawn to the screen. This container takes in the APVTS, looks up the list of parameters we have filled it with, and attaches our graphical elements to the matching parameters internally, using the previously-allocated reference name ID (such as "volumeID"). 

Finally, the Wrapper container creates and holds whatever audio effects and processors we are implementing in our plugin. Each effect/processor's internal parameters (such as "setVolume(type newVolume)" are exposed to the APVTS inside this container; these are then connected to each other by a memory allocation (such as "volumePtr"), which is written to by the parameter and read by the audio.

The Processor container provides some powerful connectivity between the APVTS and the outside world (the host). Here, the APVTS is given read/write access to memory (for presets, undo/redo, project re-loading, etc) using some XML functions. This means that every single object (usually meaning, parameter) connected to the APVTS can read from and write to it's own unique little memory address, called a "value tree". This means that our audio processor now has a memory of it's own "state" - or, rather, it has an "Audio Processor Value Tree state".

More details soon. Please see my [Biquads repo](https://github.com/StoneyDSP/Biquads) for an example implementation meanwhile :)

To be done...
+ basic GUI for the built-in parameters
+ fix precision switching
+ fix variable number of channels/buses with oversampling
+ provide more examples...

# Before you go...

Coffee! That's how I get things done!! If you'd like to see me get more things done, please kindly consider <a href="https://www.patreon.com/bePatron?u=8549187" data-patreon-widget-type="become-patron-button">buying me a coffee</a> or two ;)

<p align="center">
 <a href= "https://paypal.me/StoneyDSPAudio?country.x=ES&locale.x=en_US"><img src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif"/></a>
</p>

<p align="center">
 <a href= "https://twitter.com/Stoney_DSP/"><img src="https://github.com/StoneyDSP/StoneyDSP/blob/a075caeedffe23b2733ee38b12f9800f62aab9c2/Assets/twitter.png"/></a>
 <a href= "https://www.instagram.com/stoney_dsp/"><img src="https://github.com/StoneyDSP/StoneyDSP/blob/2253d684ba99e6c072353a94b49315162c381406/Assets/instagram.png"/></a>
 <a href= "https://www.facebook.com/StoneyDSP.Audio/"><img src="https://github.com/StoneyDSP/StoneyDSP/blob/9608562b09ee2708affd0c31117fc25a235672d9/Assets/facebook.png"/></a>
</p>
