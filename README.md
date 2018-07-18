# Semantic Image Retrieval System
Implement deep learning image semantic retrieval system.
This is a project about image semantic retrieval with the visualized operation UI. The algorithm used 'Deep Learning of Binary Hash Codes for Fast Image Retrieval(CVPRW15)', for more infomation about CVPRW15-python please view another project [cvprw15-win](https://github.com/xiaowangdu/cvprw15-win).

## Installation
Clone the project by command:
```
git clone --recursive https://github.com/xiaowangdu/Semantic-Retrieval.git
```

You need to install the caffe for windows because this project is depended on windows system. You can also consult the generic [Caffe windows installation guide](https://github.com/happynear/caffe-windows) for further help.

### Install dependencies
* [Visual Studio 2015](https://github.com/sadeepj/crfasrnn_keras) version is now available. <br/>
* [QT 5.7.0](https://github.com/sadeepj/crfasrnn_keras) version is now available. <br/>
* [Opencv 310](https://github.com/sadeepj/crfasrnn_keras) version is now available. <br/>

##### Dependent project

Clone the project [cvprw15-win](https://github.com/xiaowangdu/cvprw15-win ), it will be the base implement and provide retrieval interface for this project.
```
git clone --recursive https://github.com/xiaowangdu/cvprw15-win.git
```

### Retrieval
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/retrieval.PNG)

### Train 
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/train.PNG)
##### Caffe prototxt editor
Support syntax highlighting, bracket matching etc.
In the futhure, it will support visualizing neural network architectures.
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/prototxt_editor.PNG)

### Image preprocessing
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/preprocess.PNG)

### Label dataset
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/label.PNG)

### A simple file explorer
Support copy, cut, paste, delete and drag copy etc. You can open more than one file broswer in your will, and operate between each.
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/files.PNG)
![SemanticRetrieval](https://github.com/xiaowangdu/Semantic-Retrieval/blob/master/Pictures/files-multiwin.PNG)
