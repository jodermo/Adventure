Hi AnimChallenger!

This rig was adapted for the August "Ragdoll" Theme in collaboration with Ragdoll Dynamics!

INSTALLATION & LICENSING
STEP 1: 
Install Ragdoll Dynamics Plug-in
https://learn.ragdolldynamics.com/download/

STEP 2: 
Copy/Paste and run this script in your Maya's Script Editor, in a Python tab.
import os
from maya import cmds
from ragdoll import ui as rui, interactive as ri

text = """\
Start a new scene and activate Ragdoll Unlimited \
for the Ragdoll Dynamics August AnimChallenge?
"""

if rui.MessageBox("Activate Competition Licence", text):
    os.environ["RAGDOLL_FLOATING"] = "agora1.ragdolldynamics.com:8011"
    cmds.file(new=True, force=True)
    cmds.unloadPlugin("ragdoll")
    assert not cmds.pluginInfo("ragdoll", query=True, loaded=True), (
        "Had trouble reloading Ragdoll, try restarting "
        "Maya and running this script again"
    )
    cmds.loadPlugin("ragdoll")

    ri.welcome_user()
else:
    cmds.warning("Cancelled, nothing changed")


Handy Links: 
⁃ For more information about Ragdoll Dynamics: https://ragdolldynamics.com/
⁃ If you need any tech-help, you can find answers here: https://forums.ragdolldynamics.com/

Join your fellow AnimChallenge competitors in our Agora.Community Discord!
http://www.discord.gg/daMCPGWjc6

Ragdoll Dynamics also has a Discord! If you want to find other people to learn together you can find them here: https://discord.gg/3WbetbUEJQ

Good luck & happy animating! :)



- AnimChallenge