# MuonTomographySimulation
In this repository the source code from the simulation of a muon tomography application is presented and the results, as well.


The software toolkit used for this application is the Geant4 (https://geant4.web.cern.ch/) along with the ROOT 6.24/0.2 data analysis framework (https://root.cern/). 

Specifically the examples/extended/electromagnetic/Testem5 programme used and adjusted for our case in order to simulate cosmic muons impinging to the experimental set-up. Here, the analysis on the saved data acquired from the simulations on geant4 is presented.

The method used is the muon scattering tomography for the imaging of a lead cube and the experimental set-up is given in the picture below. It consisitd of two scintillation detectors and four MicroMegas detectors for the tracking of the muons. The detectors are assumed to have perfect resolution so the recorded positions correspond to the hit points on the detectors. The algorithm performed for the imaging of the object is the POCA algorithm which assumes a single scattering point for the recorded muons. The determination of this point can correspond to a point of the cube which is the scatterer.  

![Screenshot from 2022-08-17 17-39-03-resized](https://user-images.githubusercontent.com/63058524/185169855-ed57eadb-51e8-4dad-b728-55dac0a31514.png)

After applying the POCA algorithm and an algorithm that "clears" the image from some false poca points the following image arises, presenting the construction of the object in 3D and on the xy plane as well.

![Screenshot from 2022-08-17 17-56-35 resized](https://user-images.githubusercontent.com/63058524/185173477-e313007e-89d7-40f2-a7ee-6065e5a3054f.png)

![Screenshot from 2022-08-17 17-56-24 resized](https://user-images.githubusercontent.com/63058524/185173959-f1ab1442-2aac-4af1-8ddf-2e80d7dee772.png)
