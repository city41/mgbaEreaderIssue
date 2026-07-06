# mGBA EReader Issue

This is a tiny GBA rom that demonstrates an issue with the link cable and e-Reader in mGBA.

## To repro the issue

1. Launch mGBA with the rom: `mgba --log-level 16 game.gba`
2. Go to File > New Multiplayer Window...
3. In the new window, choose the US e-Reader ROM
4. In the e-Reader UI, go to Communication > To Game Boy Advance, then press A to connect.
5. In the game.gba window, press A

On real hardware, this will successfully send the app to the e-Reader and it will launch it without issue.

![sending the payload](https://github.com/city41/mgbaEreaderissue/blob/main/savingEreaderPayload.jpg?raw=true)

![running the payload](https://github.com/city41/mgbaEreaderissue/blob/main/runningEreaderPayload.jpg?raw=true)

On mGBA, it always results in an e-Reader communication error

![screenshot](https://github.com/city41/mgbaEreaderissue/blob/main/errorScreenshot.png?raw=true)

### Note

This app is the bare minimum to reproduce the issue.

- The GBA host screen always stays white and shows nothing of interest
  - instead it logs to mgba's log at the debug level
- The e-Reader app merely loads the cloud background and that's it.

## Environment

- mgba-qt 0.10.5 (26b7884bc25a5933960f3cdcd98bac1ae14d42e2)
- Ubuntu 24.04.4
