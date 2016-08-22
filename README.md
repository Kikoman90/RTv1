# RTv1

RTv1 is a program developped for my learning course at 42 school for the exploration of raytracing.
<img align="center" src="http://image.noelshack.com/fichiers/2016/34/1471887915-screen-shot-2016-08-22-at-7-43-03-pm.png" width="100%" />
Several options are available (see [Shortcuts](https://github.com/Kikoman90/RTv1#shortcuts) section for more info)
* Select objects within the scene
* Translate and rotate the camera
* Translate and rotate the selected object
* Increase the radius/angle of the selected object
* Increase the maximum number of reflections
* Activate reflections on planes only
* Hide or show the HUD
* Activate gloss

The program can support multiple lights and objects in a scene. The scene and objects parameters can be modified in real-time. This software also uses multitheading to fasten up the calculations. All memory allocated during execution is freed.

## Install & launch
```bash
git clone https://github.com/Kikoman90/RTv1 ~/RTv1
cd ~/RTv1 && ./RTv1 scenes/scene1.rt
```
You have to launch the program with a parameter. This is the name of the scene you would like to open at the execution of the program.
The input file has to follow a predefined layout. A parser implemented in the program will check for layout errors.<br />

Example : ⇣
```bash
./RTv1 scenes/scene5.rt
```
## Shortcuts

Once the scene is rendered, you are able to select objects in the scene by using the <kbd>&nbsp;left mouse button&nbsp;</kbd>.<br />You can exit the select mode by using the <kbd>&nbsp;return&nbsp;</kbd> key.

<table width="100%">
<thead>
<tr>
<td width="40%" height="60px" align="center" cellpadding="0">
<strong>Description</strong>
</td>
<td width="10%" align="center" cellpadding="0">
<span style="width:70px">&nbsp;</span><strong>Key(s)</strong><span style="width:50px">&nbsp;</span>
</td>
</tr>
</thead>
<tbody>
<tr>
<td valign="top" height="30px">Close the program</td>
<td valign="top" align="center"><kbd>&nbsp;esc&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;A&nbsp;</kbd> <kbd>&nbsp;D&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;W&nbsp;</kbd> <kbd>&nbsp;S&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Z axis</td>
<td valign="top" align="center"><kbd>&nbsp;+ (num)&nbsp;</kbd> <kbd>&nbsp;- (num)&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;◄&nbsp;</kbd> <kbd>&nbsp;►&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;▲&nbsp;</kbd> <kbd>&nbsp;▼&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate object along local Z axis</td>
<td valign="top" align="center"><kbd><center>&nbsp;page&nbsp;<br /> up</center></kbd> <kbd><center>&nbsp;page&nbsp;<br /> down</center></kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Activate/deactivate gloss (specularity)</td>
<td valign="top" align="center"><kbd>&nbsp;G&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease size/angle of the selected object</td>
<td valign="top" align="center"><kbd>&nbsp;+&nbsp;</kbd> <kbd>&nbsp;-&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease the maximum number of reflections</td>
<td valign="top" align="center"><kbd>&nbsp;R&nbsp;</kbd> <kbd>&nbsp;F&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Activate/deactivate reflections on planes only</td>
<td valign="top" align="center"><kbd>&nbsp;E&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Hide/show HUD</td>
<td valign="top" align="center"><kbd>&nbsp;tab&nbsp;</kbd></td>
</tr>
</tbody>
</table>
## Contact & contribute
If you want to contact me, or improve RTv1, just send me a mail at **fsidler@student.42.fr**
