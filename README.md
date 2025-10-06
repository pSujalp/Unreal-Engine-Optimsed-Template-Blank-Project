

### Already made a project? Then just go to `Config/DefaultEngine.ini` of this current Github repo project


`Copy [/Script/Engine.RendererSettings]` 

part till the next 

`[/Script/WindowsTargetPlatform.WindowsTargetSettings] `

and paste into your DefaultEngine.ini  you are working into the project you are working on your local PC . 


*Don't copy paste entire file DefaultEngine.ini as it will cause problem/conflicts and Unreal might delete regenerate a new one automatically.*
          



  *If you want to collab then pull request or put a issue in Issues tab .*

      
### This template is made with a help of Experienced devs working at Epic Games for 12 years and above and it will be updated .

# This project works with Unreal 5.6.1 and tested on Mac Silicon (M4) .It also contains Multhreading code snippets.







# Unreal Optimization Guide and Practice  (1080p / 60 FPS on GTX 970–1060)



This guide is designed for developers targeting **1080p / 60 FPS** performance on **GTX 970/1060-class GPUs** using **Unreal Engine 4.27–5.x**.  
It compiles performance budgets, best practices, and proven optimization techniques for maintaining visual quality while keeping frame times stable.



 ## Use DirectX 11 instead of 12 on Windows platform 
```
      Edit → Project Settings → Platforms → Windows 
      
      Scroll down to the section “Default RHI
      
      Change it to DirectX 11.
      
      Click Save, then restart the editor.
```

 ##                           ( OR )

# Official AMD FS3 for Unreal Engine by AMD 
  Use AMD FS3 provided by AMD but only works for **Windows** / **Vulkan** builds (DirectX 12/Vulkan)

  **DirectX 11 not supported except for AMD-FSR1**

     
         
<img width="256" height="288" alt="Image" src="https://github.com/user-attachments/assets/70524c20-22a2-411f-8e32-8b340ba649fb" />



  
   [Official FSR 3 plugin for Unreal Engine 5.6+ ](https://gpuopen.com/learn/ue-fsr3/)                                                      


   [Official FSR 4 plugin for Unreal Engine 5.6+ ](https://gpuopen.com/learn/ue-fsr4/))

   

   **Checkout their Fab/Unreal MarketPlace** - [Fab/Unreal MarketPlace](https://www.fab.com/sellers/GPUOpen)

   # **Note** - **FSR1** works for all the platforms

   ###      check what you can implement in your project by your version number (Has support for 4.27 , 5.1 and 5.6 )

   
   

   

  

  

---

##  Performance Budgets

| Metric | Target |
|--------|---------|
| Frame Time | ≤ 16.6 ms (60 FPS) |
| Draw Calls | < 3 000 |
| Triangles | ≤ 12 Million |
| Texture Resolution | Mostly ≤ 2K (4K for hero assets only) |

---

##  Geometry & World

- **Disable Nanite** for GTX-class GPUs.  
- Use **Hierarchical Instanced Static Meshes (HISMA)** or **Instanced Static Meshes (ISM)** for repeated assets.  
- Always **Generate LODs** (even with Nanite enabled).  
- Employ **custom lightweight HLODs** — Epic’s system can be memory-heavy.  
- Replace decals with **mesh cards** where possible.  
- Set **max draw distances** for small meshes and lights.  
- Use **simple collisions** only — disable collision and `Affect Nav Mesh` on decorative objects.  
- Use **World Partition** with **small cells** for efficient streaming.  
- Aggressively manage **LOD transitions** and use **instancing** to minimize draw calls.  

---

##  Lighting

- Prefer **1 dynamic key light + baked fill lighting**.  
- Use a **static skylight** with **baked cubemaps** (no real-time reflection captures).  
- **Avoid Lumen** if possible — use baked lighting for static scenes.  
- Minimize **SDF and volumetric** effects.  
- **Disable shadows** on small objects; use **proxy shadow casters** for complex ones.  
- Use **capsule shadows** on skeletal meshes.  
- Replace **volumetric fog/clouds** with **fake light rays** (cards or shaders).  
- **Sphere Reflection Probes:** bake and reuse cubemaps.  
- A fully baked setup can ship with **zero dynamic lights**.  

---

##  Materials & Shading

- Keep materials ≤ 6–8 texture samples.  
- **No tessellation.**  
- **Limit parallax and bump offsets** (texture-dependent).  
- Prefer **dithering** over transparency; fake glass with **cubemaps/shaders**.  
- Use **Anisotropic Relaxed Cone** instead of POM.  
- **Pack ORM** maps to reduce texture count.  
- Split **alpha channels** into separate textures when possible.  
- Derive **normal B channel** from RG to save space.  
- Assign all textures to **proper groups** for easy management.  
- Set **shading rate > 1×1** for VFX/skybox to reduce pixel cost.  

---

##  Memory Management

- **Pack multiple masks** into one texture (slice maps).  
- **Avoid RGBA textures** when unused channels exist.  
- **Albedo/Normal** can be 2K, while **Spec/Masks/ORM** can be 1K.  
- Disable **“Generate Lightmap UVs”** on meshes using dynamic lighting.  
- Remove **extra UV channels** on all meshes.  
- Manage the **texture streaming pool** — increase or optimize it to avoid VRAM thrashing.  

---

##  Skeletal Meshes

- **Reduce bone count** aggressively.  
- **Blendshapes only for cinematics.**  
- Replace destruction animations with **Vertex Animation Textures (VATs)**.  
- **Capsule shadows** instead of complex shadow casting.  
- Disable **per-frame tick** on non-critical Blueprints.  

---

##  Dynamics & VFX

- **Chaos Physics/Destruction** is expensive — bake results where possible.  
- **Cloth:** avoid Chaos Cloth; use **dynamic bone chains** or pre-baked simulations.  
- Replace **projectile traces** with particles or ray approximations.  
- Bake **flipbooks** for fire, smoke, or liquids instead of dynamic sims.  
- **Niagara:** use LODs; disable particle lights at Medium and below.  
- Use **particle cutouts** to minimize overdraw.  

---

##  Post-Processing

- **Bloom:** Low  
- **Chromatic Aberration:** Off  
- **Motion Blur:** ≤ 0.3  
- **SSR/SSAO:** Off or Low  
- **Fog:** Use simple exponential fog only  
- Prefer **fake DOF** or none  

---

## Scalability & Quality Settings

Default target: **Medium**

| Setting | Recommendation |
|----------|----------------|
| Screen Percentage | ~85% |
| Upscaler | TAAU or FSR 2 |
| Shadows | ≤ 2 cascades, max 2048 res |
| SSR | Disabled |
| SSAO | Low/Off |
| Volumetric Effects | Off |
| Reflection Capture | Baked only |

---

###  Shipping Low-Spec Toggle
For ultra-low hardware fallback:

```
r.ScreenPercentage 80
r.Fog 0
r.AmbientOcclusionLevels 0
r.Shadow.MaxResolution 1024
```

---

##  Profiling & Testing

- Use **Stat Unit**, **Stat GPU**, **ProfileGPU**, and **Session Frontend** early in development.  
- Test builds on **real GTX 970/1060 hardware** — synthetic scaling isn’t reliable.  
- Monitor **VRAM usage** and **texture pool overflow warnings**.  

---

##  Engine Choice

💡 **Alternative:** Use **Unreal Engine 4.27** for lighter rendering and no Lumen overhead — ideal for GTX and midrange GPUs.

---

##  Custom Scalability Tiers

Define your own scalability tiers in `Scalability.ini` rather than relying on Epic’s defaults.  
Fine-tune toggles for post, shadows, and material complexity per-tier for consistent visual quality across low/mid hardware.

---

## Summary

**Goal:** Stable 60 FPS @ 1080p on GTX 970/1060  
**Core Principles:**
- Aggressive LODs & instancing  
- Static lighting & baked reflections  
- Optimized materials & texture packing  
- Minimal dynamic systems (physics, lights, particles)  
- Strong profiling discipline  

---

**Author Notes**  
> Many of these practices trace back to the Unreal 2–4 era — and still work wonders in UE5.  
> Don’t underestimate the power of disciplined LODs, instancing, and clean material setups.  
> You can ship a gorgeous UE5 game on GTX-class GPUs — if you’re smart about every millisecond.
