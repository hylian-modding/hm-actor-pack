# Hylian Modding OoT Decomp Actor Pack

This is a custom actor pack intended for use with the [Ocarina of Time decompilation project by ZeldaRET.](https://github.com/zeldaret/oot)

In this pack, you'll find the following custom actors:
* **Scalable, rotatable fans**
  * Push Link and bombs around
  * By Aegiker and CDi-Fails
* **Floor spikes with various modes** 
  * Cyclic, pressure-sensitive, switch flag dependent, etc.
  * Code by hiisuya, assets by CDi-Fails
* **Hammer pegs**
  * Useful for blocking players before they have the hammer
  * By CDi-Fails
* **Red/blue platforms**
  * Toggle between two rotations when Link leaves the ground
  * Code by kentonm, assets by kentonm and CDi-Fails
* **Configurable ladders**
  * Wooden (hookshotable) or metal (non-hookshotable)
  * Can either fade in on switch flag, or drop to the ground when hit with bow/slingshot
  * By CDi-Fails
* **Metal crates**
  * Can only be broken with the hammer 
  * By kentomm
* **Configurable platforms**
  * Various themes/textures
  * Can either fade in on switch flag, or hover in the air
  * By hiisuya
* **Wall pull switch**
  * Can retract on a timer and unset switch flag when fully retracted 
  * Code by kentonm, assets by CDi-Fails
* **Rat enemy**
  * By CDi-Fails
* **Pols Voice enemy**
  * Weak to arrows and Ocarina songs
  * Code by CDi-Fails, LuigiXHero, and hiisuya; assets by CDi-Fails
* **Wizzrobe enemy**
  * Attacks with fire and ice spells
  * Can spawn other enemies 
  * Code by ZeeRoX, assets by Syeo
* **Zol enemy**
  * Slime monster that can split in two
  * By ZeeRoX

You can find notes for each of these actor inside their C source files located at ``src/overlays/actors/hm_pack/``.

**Originally created by**:
* CDi-Fails
* kentonm
* hiisuya
* ZeeRoX & Syeo
* Aegiker

For more information, visit us at the links below:

* **Website:** <https://hylianmodding.com/>
* **Discord:** <https://discord.com/invite/nGFZ394>

## Setting up

There are two recommended ways you can get started with this actor pack.

### Method #1 - Copy & Paste
This method is best suited for those wishing to incorporate the actor pack into an existing modded repo. If you don't already have a repo set up and building, follow the [OoT decomp installation guide.](https://github.com/zeldaret/oot#installation). Make sure you have the MIPS GCC compiler. If you don't, install it by running this command:
```
sudo apt-get install gcc-mips-linux-gnu
```

First, copy all of the following into your repo:

```
Makefile
spec
spec.hm_pack_actors.inc
spec.hm_pack_objects.inc
assets_hm_pack/
src/overlays/actors/hm_pack/
include/tables/hm_pack/
include/tables/actor_table.h
include/tables/object_table.h
```

If you're uncomfortable overwriting the Makefile and/or spec, or if the decomp repo has made changes we haven't merged into this repo yet, just make sure you copy over the relevant changes to your files.

Now, run the following commands:
```
make clean && make setup && make
```
You should now have a ROM built successfully!

### Method #2 - Cloning This Repo
If you want to start your modding project from scratch using this actor pack as a base, this method is for you. Simply ``git clone`` this repo, then follow the OoT decomp installation guide as normal. Make sure you have the MIPS GCC compiler as well. If you don't, run:
```
sudo apt-get install gcc-mips-linux-gnu
```

**NOTE:** There's always a chance that this repo is out of sync with the main decomp repo. To ensure you're not missing anything, we recommend you add the main decomp repo as a remote, then fetch and merge the latest commits. It's good practice to do this often. Here's how to start:
```
git remote add upstream [GIT CLONE LINK FOR OOT DECOMP REPO]
git fetch upstream
git merge upstream/main
```

### Setting up the test map
Included with this actor pack is a preconfigured test map intended to showcase all the actors in this pack. If you'd like to check it out, you'll need to add it to your repo manually. This involves adding: the scene and rooms files to spec, an entry for it in scene_table.h, entrances for it in entrance_table.h, and a map select entry for it in z_select.

Start by adding the scene and room files at the end of the `spec` file:
```
beginseg
    name "test_map_scene"
    romalign 0x1000
    include "$(BUILD_DIR)/assets_hm_pack/scenes/test_map/test_map_scene.o"
    number 2
endseg

beginseg
    name "test_map_room_0"
    romalign 0x1000
    include "$(BUILD_DIR)/assets_hm_pack/scenes/test_map/test_map_room_0.o"
    number 3
endseg

beginseg
    name "test_map_room_1"
    romalign 0x1000
    include "$(BUILD_DIR)/assets_hm_pack/scenes/test_map/test_map_room_1.o"
    number 3
endseg

beginseg
    name "test_map_room_2"
    romalign 0x1000
    include "$(BUILD_DIR)/assets_hm_pack/scenes/test_map/test_map_room_2.o"
    number 3
endseg
```

Next, add an entry for the map at the end of `include/tables/scene_table.h`:
```
DEFINE_SCENE(test_map_scene, none, SCENE_TEST_MAP, SDC_DEFAULT, 0, 0)
```

Then, add entrances for the map at the end of ``include/tables/entrance_table.h``
```
DEFINE_ENTRANCE(ENTR_TEST_MAP_0, SCENE_TEST_MAP, 0, false, true, TRANS_TYPE_FADE_BLACK, TRANS_TYPE_FADE_BLACK)
DEFINE_ENTRANCE(ENTR_TEST_MAP_0_1, SCENE_TEST_MAP, 0, false, true, TRANS_TYPE_FADE_BLACK, TRANS_TYPE_FADE_BLACK)
DEFINE_ENTRANCE(ENTR_TEST_MAP_0_2, SCENE_TEST_MAP, 0, false, true, TRANS_TYPE_FADE_BLACK, TRANS_TYPE_FADE_BLACK)
DEFINE_ENTRANCE(ENTR_TEST_MAP_0_3, SCENE_TEST_MAP, 0, false, true, TRANS_TYPE_FADE_BLACK, TRANS_TYPE_FADE_BLACK)
```

Finally, add a map select entry at the end of the ``sScenes`` array in ``src/overlays/gamestates/ovl_select/z_select.c`` (after the title screen entry):
```
{ "HM Pack Test Map", MapSelect_LoadGame, ENTR_TEST_MAP_0 },
```

Run the following commands:
```
make clean && make setup && make
```

Now boot into the game, go to map select, and select the `HM Pack Test Map` entry. You should be in the test map and see all of the new actors!
