# Forward Render

This plugin is intended to replace the Hotpatch module described here: https://blog.daftsoftware.com/unreal-perf-maxing/

Additionally, it will also optionally update the MPC parameter with the Directional Light's forward vector for material/rendering purposes during editor time using an `FTickableEditorObject`

> [!NOTE]
> This will not update the light vector during PIE and you should implement this behaviour in your project wherever appropriate

## Resources

Consider also reading Valorant's guide for polished results under forward rendering here: https://technology.riotgames.com/news/valorant-shaders-and-gameplay-clarity

## Usage

Typically you will want to first complete the guide linked above to get setup with mobile forward rendering. But don't do the hotpatch module.

Clone this plugin to your project. There is no LFS content so you can also download as a zip.

You will need to build your project from your IDE; binaries are not offered here.

Once the plugin is installed and enabled, load the editor and you should see that it is now in mobile preview:

<img width="401" height="102" alt="image" src="https://github.com/user-attachments/assets/486025f2-7ec9-409e-93a5-b7503b6ba006" />

## Light Vector

Open Project Settings -> Editor -> Forward Render Settings

<img width="747" height="350" alt="image" src="https://github.com/user-attachments/assets/50a69025-54a9-441e-964f-daa689fec20c" />

If you do not wish for the editor to update a light vector you can disable this behaviour here.

Otherwise, create a material parameter collection if you don't already have one and assign it. Create and assign the LightVector parameter.

> [!WARNING]
> Click `Set as Default` or your settings will potentially revert

# Changelog

### 1.0.1
* Disable preview platform on Linux (not supported)

## 1.0.0
* Initial Commit
