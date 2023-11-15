# Hylian Modding OoT Decomp Actor Pack

This is a custom actor pack intended for use with the [Ocarina of Time decompilation project by ZeldaRET.](https://github.com/zeldaret/oot)

In this pack, you'll find the following custom actors:
* **Scalable, rotatable fans**
  * Push Link and bombs around 
* **Floor spikes with various modes** 
  * Cyclic, pressure-sensitive, switch flag dependent, etc.
* **Hammer pegs**
  * Useful for blocking players before they have the hammer
* **Red/blue platforms**
  * Toggle between two rotations when Link leaves the ground
* **Configurable ladders**
  * Wooden (hookshotable) or metal (non-hookshotable)
  * Can either fade in on switch flag, or drop to the ground when hit with bow/slingshot
* **Metal crates**
  * Can only be broken with the hammer 
* **Configurable platforms**
  * Various themes/textures
  * Can either fade in on switch flag, or hover in the air
* **Wall pull switch**
  * Can retract on a timer and unset switch flag when fully retracted 
* **Rat enemy**
* **Pols Voice enemy**
  * Weak to only arrows 
* **Wizzrobe enemy**
  * Attacks with fire and ice spells
  * Can spawn other enemies 
* **Zol enemy**
  * Slime monster that can split in two 

You can find notes for each of these actor inside their C source files located at ``src/overlays/actors/hm_pack/``.

**Created by**:
* CDi-Fails
* kentonm
* hiisuya
* ZeeRoX
* Aegiker

For more information, visit us at the links below:

* **Website:** <https://hylianmodding.com/>
* **Discord:** <https://discord.com/invite/nGFZ394>

## Setting up

There are a few ways that you can get started with this actor pack.

### Method #1 - Git Patches
We recommend you try this method first. To begin, follow the [installation guide for the Ocarina of Time decompilation project](https://github.com/zeldaret/oot#installation) to get a repository up and running. Once you have a ROM building, download the `hm_pack.patch` file (and optionally, `hm_pack_test_map.patch`) from here. Place the patches in the root folder of your base OoT decomp repo. Next, run the following command:

```
git apply hm_pack.patch
```

You may see some warnings about whitespace or line breaks-- that's okay. Check in your repo's root folder to see if there's an `assets_hm_pack` folder. If so, it's likely the patch has worked!

Now, you can optionally do the same for the `hm_pack_test_map.patch` file to add a test map with example use cases for all the actors in this pack. It will appear at the end of the map select in the game.
```
git apply hm_pack_test_map.patch
```

Finally, run:
```
make distclean && make setup && make
```
If all went well, the built ROM should contain the actors (and test map, if you applied that patch)!

### Method #2 - Copy & Paste
This method is more suited for those wishing to incorporate the actor pack into an existing modded repo. We'll assume you already have a repo set up and can build a ROM with it. First, copy all of the following into your repo:

```
Makefile
spec.hm_pack_actors.inc
spec.hm_pack_objects.inc
assets_hm_pack/
src/overlays/actors/hm_pack/
include/tables/hm_pack/
```

If you're uncomfortable overwriting the Makefile, or if the decomp repo has made changes to it we haven't merged into this repo yet, just make sure you copy over the relevant changes to yours. If you want to add the test map, you'll have to add: the scene and rooms files to spec, an entry for it in scene_table.h, entrances for it in entrance_table.h, and a map select entry for it in z_select. Now, run the following commands:
```
make distclean && make setup && make
```
You should now have a ROM built successfully!

### Method #3 - Cloning This Repo
If you want to start your modding project from scratch using this actor pack as a base, this method is for you. Simply ``git clone`` this repo, then follow the OoT decomp installation guide as normal.

**NOTE:** There's always a chance that this repo is out of sync with the main decomp repo. To ensure you're not missing anything, we recommend you add the main decomp repo as a remote, then fetch and merge the latest commits. It's good practice to do this often. Here's how to start:
```
git remote add upstream [GIT CLONE LINK FOR OOT DECOMP REPO]
git fetch upstream
git merge upstream/main
```
