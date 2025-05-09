/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        g3dm.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 09.09.2024
 * PURPOSE:     RayTracing's g3dm header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __g3dm_h_
#define __g3dm_h_

#include "../rt_def.h"
#include "../mtl/material_manager.h"
#include "../tex/texture.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Convert float vector to double vector.
     * ARGUMENTS:
     *   - float vector:
     *       const fvec3 &V;
     * RETURNS:
     *   (vec3) new vector.
     */
    inline vec3 ConvertFVtoDV3( const fvec3 &V )
    {
      return vec3(V.X, V.Y, V.Z);
    } /* End of 'ConvertFVtoDV3' function */

    /* Convert float vector to double vector.
     * ARGUMENTS:
     *   - float vector:
     *       const fvec2 &V;
     * RETURNS:
     *   (vec2) new vector.
     */
    inline vec2 ConvertFVtoDV2( const fvec2 &V )
    {
      return vec2(V.X, V.Y);
    } /* End of 'ConvertFVtoDV2' function */

    /* Declare polygon class */
    class polygon;

    /* Struct with intersection data (for prim_storage) */
    struct pr_intr
    {
      const polygon *Pol; // Intersected polygon
      DBL           T;    // Intersection ray distance
      vec3          P;    // Position
      vec3          N;    // Normal
    }; /* End of 'pr_intr' function */

    /* Polygon class */
    class polygon
    {
    public:
      vec3
        P1, P2, P3,    // points of triangle
        N,             // normal of triangle
        U1, V1;        // vectors for search u & v
      DBL
        u0, v0;        // coef for search u & v
      vec2
        TC1, TC2, TC3; // texture coordinates

      /* Polygon constructor
       * ARGUMENTS:
       *   - points:
       *       const vec3 &p1, &p2, &p3;
       *   - texture coordinates:
       *       const vec2 &tc1, &tc2, &tc3;
       */
      polygon( const vec3 &p1, const vec3 &p2, const vec3 &p3, 
               const vec2 &tc1, const vec2 &tc2, const vec2 &tc3 ) :
        P1(p1), P2(p2), P3(p3), TC1(tc1), TC2(tc2), TC3(tc3)
      {
        N = ((p2 - p1) % (p3 - p1)).Normalizing();
        vec3 s1 = p2 - p1;
        vec3 s2 = p3 - p1;
        
        U1 = (s1 * s2.Len2() - s2 * (s1 & s2)) / (s1.Len2() * s2.Len2() - (s1 & s2) * (s1 & s2));
        u0 = P1 & U1;

        V1 = (s2 * s1.Len2() - s1 * (s1 & s2)) / (s1.Len2() * s2.Len2() - (s1 & s2) * (s1 & s2));
        v0 = P1 & V1;
      } /* End of 'polygon' function */

      /* Get intersection function.
       * ARGUMENTS:
       *   - reference to ray:
       *       const ray &R;
       *   - pointer to intersection structure:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) status of success intersection.
       */
      BOOL IsIntersect( const ray &R, pr_intr *Intr ) const
      {
        DBL T = (N & (P1 - R.Org)) / (N & R.Dir);

        if (T < Treashold)
          return FALSE;

        Intr->P = R.Org + R.Dir * T;

        DBL u = (Intr->P & U1) - u0;

        if (u < Treashold)
          return FALSE;

        DBL v = (Intr->P & V1) - v0;

        if (v < Treashold)
          return FALSE;

        if (u + v - 1 > Treashold)
          return FALSE;

        Intr->N = N;
        Intr->T = T;
        Intr->Pol = this;

        return TRUE;
      } /* End of 'IsIntersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) const
      {
        Intr->N = N;
      } /* End of 'GetNormal' function */

      /* Get texture coordinates function.
       * ARGUMENTS:
       *   - intersection:
       *       intr *Intr;
       * RETURNS:
       *   (vec2) texture coordinates.
       */
      vec2 GetTC( const vec3 &P ) const
      {
        DBL u = (P & U1) - u0;
        DBL v = (P & V1) - v0;
        DBL w = 1 - u - v;

        //assert(u < 1 && v < 1 && u > 0 && v > 0 && u + v < 1);

        return TC1 * u + TC2 * v + TC3 * w;
      } /* End of 'GetColor' function */

    }; /* End of 'polygon' class */

    /* Vertex struct */
    struct vertex
    {
      // We used vec3<float>, because g3dm
      // storage numbers in FLOAT data type.
      fvec3 P;  // Position
      fvec2 TC; // Texture coordinates
      fvec3 N;  // Normal
      fvec4 C;  // Color (not used, storage in G3DM)
    }; /* End of 'vertex' struct */

    /* Primitive's polygons storage class */
    class prim_storage
    {
    public:
      /* Get data about position of polygon inside the bound box function.
       * ARGUMENTS:
       *   - polygon points:
       *       const vec3 &P1, &P2, &P3;
       *   - bound box:
       *       const vec3 &MinBB, &MaxBB;
       * RETURNS:
       *   (BOOL) true - if inside, else false.
       */
      static BOOL PolIsInside( const vec3 &P1, const vec3 &P2, const vec3 &P3, const vec3 &MinBB, const vec3 &MaxBB )
      {
        return
          (P1.X - MinBB.X > Treashold && P1.X - MaxBB.X < Treashold &&
           P2.X - MinBB.X > Treashold && P2.X - MaxBB.X < Treashold &&
           P3.X - MinBB.X > Treashold && P3.X - MaxBB.X < Treashold &&
           P1.Y - MinBB.Y > Treashold && P1.Y - MaxBB.Y < Treashold &&
           P2.Y - MinBB.Y > Treashold && P2.Y - MaxBB.Y < Treashold &&
           P3.Y - MinBB.Y > Treashold && P3.Y - MaxBB.Y < Treashold &&
           P1.Z - MinBB.Z > Treashold && P1.Z - MaxBB.Z < Treashold &&
           P2.Z - MinBB.Z > Treashold && P2.Z - MaxBB.Z < Treashold &&
           P3.Z - MinBB.Z > Treashold && P3.Z - MaxBB.Z < Treashold ) ?
          TRUE : FALSE;
      } /* End of 'PolIsInside' function */

      /* Get data about intersection ray and bound box
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - bound box:
       *       const vec3 &MinBB, MaxBB;
       * RETURNS:
       *   (BOOL) 
       */
      static BOOL BBIsIntersected( const ray &R, const vec3 &MinBB, const vec3 &MaxBB )
      {
        // Normals
        static vec3 N[6] = 
        {
          vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1),
          vec3(1, 0, 0),  vec3(0, 1, 0),  vec3(0, 0, 1)
        };
        // Positions
        const vec3 (&P)[6] =
        {
          MinBB, MinBB, MinBB, MaxBB, MaxBB, MaxBB
        };
    
        // Consider each side of the cube
        for (INT i = 0; i < 6; ++i)
        {
          // Find the intersection with the planes of sides
          DBL T = (N[i] & (P[i] - R.Org)) / (N[i] & R.Dir);

          if (T < Treashold)
            continue;

          // Check that the intersection occurred within
          // the limit of the side of the square.
          vec3 PPP = R(T);

          if (PPP.X - MinBB.X > Treashold && PPP.X - MaxBB.X < Treashold &&
              PPP.Y - MinBB.Y > Treashold && PPP.Y - MaxBB.Y < Treashold &&
              PPP.Z - MinBB.Z > Treashold && PPP.Z - MaxBB.Z < Treashold)
            return TRUE;
        }

        // If there is no intersection with any side,
        // then the ray does not intersect the cube.
        return FALSE;
      } /* End of 'BBIsIntersected' function */

      static constexpr INT 
        MaxDeep = 8; // Max deep of prim storage.

      prim_storage 
        *Less {},     // Pointer to less storage element
        *More {};     // Pointer to more storage element
      INT
        CurrentDeep; // Deep of this element.
      vec3
        MinBB,       // Min bound box
        MaxBB;       // Max bound box
      std::vector<polygon>
        Triangles;   // Array with current triangles
      
      /* Delete copy constructor */
      prim_storage( const prim_storage &S ) = delete;

      /* Default constructor.
       * ARGUMENTS:
       *   - array with current (for this deep level) polygons:
       *       const std::vector<polygon> &CurPol;
       *   - current bound box:
       *       vec2 CurMinBB, CurMaxBB;
       *   - current deep:
       *       INT deep;
       */
      prim_storage( const std::vector<polygon> &CurPol, const vec3 &CurMinBB, const vec3 &CurMaxBB, INT CurDir ) : 
        MinBB(CurMinBB), MaxBB(CurMaxBB), CurrentDeep(CurDir)
      {
        // If achived max recursion deep level, 
        // then all current polygons add to this storage element
        if (CurDir >= prim_storage::MaxDeep)
        {
          Triangles = CurPol;
          return;
        }

        // Initialize polygon arrays for more and less storage elements
        std::vector<polygon> MorePol;
        std::vector<polygon> LessPol;

        // Bound boxes for more and less storage elements
        vec3 LessMinBB = CurMinBB;
        vec3 LessMaxBB = {CurMinBB.X / 2 + CurMaxBB.X / 2, CurMaxBB.Y, CurMaxBB.Z};
        vec3 MoreMinBB = {CurMinBB.X / 2 + CurMaxBB.X / 2, CurMinBB.Y, CurMinBB.Z};
        vec3 MoreMaxBB = CurMaxBB;

        for (auto &i : CurPol)
        {
          if (PolIsInside(i.P1, i.P2, i.P3, LessMinBB, LessMaxBB))
            LessPol.push_back(i);
          else if (PolIsInside(i.P1, i.P2, i.P3, MoreMinBB, MoreMaxBB))
            MorePol.push_back(i);
          else
            Triangles.push_back(i);
        }

        // Ñreate new tree elements recursively
        if (!LessPol.empty())
          Less = new prim_storage(LessPol, LessMinBB, LessMaxBB, CurDir + 1);
        if (!MorePol.empty())
          More = new prim_storage(MorePol, MoreMinBB, MoreMaxBB, CurDir + 1);
      } /* End of 'prim_storage' class */

      /* Default destructor */
      ~prim_storage()
      {
        if (Less != nullptr)
          delete Less, Less = nullptr;
        if (More != nullptr)
          delete More, More = nullptr;
      } /* End of '~prim_storage' function */

      /* Get intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersections structure:
       *       pr_intr *Intr;
       * RETURNS:
       *   (BOOL) is intersect flag.
       */
      BOOL Intersect( const ray &R, pr_intr *Intr )
      {
        pr_intr tmp;
        DBL BestT = -1;

        if (Less != nullptr && Less->BBIsIntersected(R, MinBB, MaxBB))
          if (Less->Intersect(R, &tmp) && (BestT > tmp.T || BestT == -1))
            BestT = tmp.T, *Intr = tmp;
        if (More != nullptr && More->BBIsIntersected(R, MinBB, MaxBB))
          if (More->Intersect(R, &tmp) && (BestT > tmp.T || BestT == -1))
            BestT = tmp.T, *Intr = tmp;

        for (auto &i : Triangles)
          if (i.IsIntersect(R, &tmp) && (BestT > tmp.T || BestT == -1))
            BestT = tmp.T, *Intr = tmp;
        
        return BestT == -1 ? FALSE : TRUE;
      } /* End of 'Intersect' function */

      /* Get all intersections function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - all intersections list:
       *       std::vector<pr_intr> &Il;
       * RETURNS:
       *   (INT) count of intersections in this level.
       */
      INT AllIntersect( const ray &R, std::vector<pr_intr> &Il )
      {
        pr_intr tmp;
        DBL BestT = -1;
        INT count {};

        if (Less != nullptr && Less->BBIsIntersected(R, MinBB, MaxBB))
          count += Less->AllIntersect(R, Il);
        if (More != nullptr && More->BBIsIntersected(R, MinBB, MaxBB))
          count += More->AllIntersect(R, Il);

        for (auto &i : Triangles)
          if (i.IsIntersect(R, &tmp))
            Il.push_back(tmp), ++count;
        
        return count;
      } /* End of 'AllIntersect' function */

    }; /* End of 'prim_storage' class */

    /* Primitive class */
    class prim : public shape
    {
    private:
      /* Get bound box function.
       * ARGUMENTS:
       *   - array with polygons:
       *       const std::vector<polygon> &V;
       *   - pointer to bound box vectors:
       *       vec3 *MinBB, *MaxBB;
       */
      static VOID GetMinMaxBB( const std::vector<polygon> &V, vec3 *MinBB, vec3 *MaxBB )
      {
        *MinBB = V[0].P1;
        *MaxBB = V[0].P1;

        for (auto &i : V)
        {
          if (MinBB->X > i.P1.X)
            MinBB->X = i.P1.X;
          if (MinBB->Y > i.P1.Y)
            MinBB->Y = i.P1.Y;
          if (MinBB->Z > i.P1.Z)
            MinBB->Z = i.P1.Z;

          if (MaxBB->X < i.P1.X)
            MaxBB->X = i.P1.X;
          if (MaxBB->Y < i.P1.Y)
            MaxBB->Y = i.P1.Y;
          if (MaxBB->Z < i.P1.Z)
            MaxBB->Z = i.P1.Z;

          if (MinBB->X > i.P2.X)
            MinBB->X = i.P2.X;
          if (MinBB->Y > i.P2.Y)
            MinBB->Y = i.P2.Y;
          if (MinBB->Z > i.P2.Z)
            MinBB->Z = i.P2.Z;

          if (MaxBB->X < i.P2.X)
            MaxBB->X = i.P2.X;
          if (MaxBB->Y < i.P2.Y)
            MaxBB->Y = i.P2.Y;
          if (MaxBB->Z < i.P2.Z)
            MaxBB->Z = i.P2.Z;

          if (MinBB->X > i.P3.X)
            MinBB->X = i.P3.X;
          if (MinBB->Y > i.P3.Y)
            MinBB->Y = i.P3.Y;
          if (MinBB->Z > i.P3.Z)
            MinBB->Z = i.P3.Z;

          if (MaxBB->X < i.P3.X)
            MaxBB->X = i.P3.X;
          if (MaxBB->Y < i.P3.Y)
            MaxBB->Y = i.P3.Y;
          if (MaxBB->Z < i.P3.Z)
            MaxBB->Z = i.P3.Z;
        }
      } /* End of 'GetMinMaxBB' function */
      
      prim_storage *Entry {};    // Entry to prim storage tree
      //const polygon *CurPl {}; // Current polygon

    public:
      INT MtlNo {};              // Number of material in stock
      vec3
        MinBB, MaxBB;            // Bound box.

      /* Constructor of primitive by vertexes and indices function
       * ARGUMENTS:
       *   - array with vertexes:
       *       const std::vector<vertex> &V;
       *   - array with indices:
       *       const std::vector<INT> &I;
       */
      prim( const std::vector<vertex> &V, const std::vector<INT> &I )
      {
        assert(!I.empty());

        std::vector<polygon> PArr;
        vec3 minbb, maxbb;

        for (INT i = 0; i < I.size(); i += 3)
          PArr.push_back({ConvertFVtoDV3(V[I[i]].P), 
                          ConvertFVtoDV3(V[I[i + 1]].P), 
                          ConvertFVtoDV3(V[I[i + 2]].P),
                          ConvertFVtoDV2(V[I[i]].TC), 
                          ConvertFVtoDV2(V[I[i + 1]].TC), 
                          ConvertFVtoDV2(V[I[i + 2]].TC)});
        
        GetMinMaxBB(PArr, &minbb, &maxbb);

        Entry = new prim_storage(PArr, minbb, maxbb, 0);
        MinBB = minbb;
        MaxBB = maxbb;
        IsUsingMod = TRUE;
      } /* End of 'prim' function */

      /* Primitive constructor */
      prim( prim &&Other ) noexcept
      {
        MtlNo = Other.MtlNo;
        Surf = Other.Surf;
        material = Other.material;
        MinBB = Other.MinBB;
        MaxBB = Other.MaxBB;
        IsUsingMod = TRUE;
        std::swap(Entry, Other.Entry);
      } /* End of 'prim' function */ 

      ///* Delete copy constructor */
      //prim( const prim &P ) = delete;

      /* Default destructor */
      ~prim( VOID ) override
      { 
        if (Entry != nullptr)
          delete Entry, Entry = nullptr;
      } /* End of '~prim' function' */

      /* Get intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersection structure:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) status of success intersection.
       */
      BOOL Intersect( const ray &R, intr *Intr )
      {
        pr_intr in;

        if (Entry->Intersect(R, &in))
        {
          Intr->T = in.T;
          Intr->Ptr[0] = reinterpret_cast<const VOID *>(in.Pol);
          Intr->Shp = this;
          GetNormal(Intr);

          return TRUE;
        }

        return FALSE;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) override
      {
        reinterpret_cast<const polygon *>(Intr->Ptr[0])->GetNormal(Intr);
      } /* End of 'GetNormal' function */

      /* Get all intersects function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - list with intersections:
       *       intr_list &Il;
       * RETURNS:
       *   (INT) Count of intersections.
       */
      INT AllIntersect( const ray &R, intr_list &Il ) override
      {
        std::vector<pr_intr> Inters;

        INT size = Entry->AllIntersect(R, Inters);

        if (!size)
          return 0;

        for (auto &i : Inters)
        {
          intr In;
          In.T = i.T;
          In.Ptr[0] = reinterpret_cast<const VOID *>(i.Pol);
          In.Shp = this;
          Il.push_back(In);
        }

        return size;
      } /* End of 'AllIntersect' function */

      /* Get information about insiding location point in shape function.
       * ARGUMENTS:
       *   - point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) true - if point inside, else false.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        return FALSE;
        //std::vector<pr_intr> Inters;
        //
        //return Entry->AllIntersect(ray(P, vec3(0, 1, 0)), Inters);
      } /* End of 'IsInside' function */

      /* Get information about intersect ray of shape function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       * RETURNS:
       *   (BOOL) true - if ray intersect, else false.
       */
      BOOL IsIntersect( const ray &R ) override
      {
        pr_intr in;

        return Entry->Intersect(R, &in);
      } /* End of 'IsIntersect' function */

      /* Update surface function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateSurf( VOID )
      {
        //if (MtlNo != 0)
        shape::Surf = *MtlManager.GetSurfByNo(MtlNo);
      } /* End of 'UpdateSurf' function */

      /* Modificate color of shape function.
       * ARGUMENTS:
       *   - position of drawing:
       *       const vec3 &Pos;
       *   - normal:
       *       const vec3 &N;
       *   - intersection:
       *       intr *In;
       * RETURNS:
       *   (vec3) color.
       */
      vec3 Mode( const vec3 &Pos, const vec3 &N, intr *In ) override
      {
        if (Surf.TexNum[0] != -1)
        {
          //if (In->V[0] != In->P)
          //{
            //printf("%lf%lf%lf %lf%lf%lf\n", In->V[0].X, In->V[0].Y, In->V[0].Z, In->P.X, In->P.Y, In->P.Z);
          //}
          return TexManager.GetTexByNo(Surf.TexNum[0])->GetColor(reinterpret_cast<const polygon *>(In->Ptr[0])->GetTC(In->V[0]));
        }
        return Surf.Kd;
      } /* End of 'Mode' function */

    }; /* End of 'prim' class */

    /* G3DM Model class */
    class g3dm : public shape
    {
    public:
      std::vector<prim> Prims; // Array with prims

      /* Constructor of g3dm */
      g3dm( std::string filename )
      {
        FILE *F;
        INT flen;
        BYTE *mem, *ptr;
        DWORD
          Sign, /* == "G3DM" */
          NumOfPrims,
          NumOfMaterials,
          NumOfTextures;
        INT p, t, m;
 
        /* Open file */
        if ((F = fopen(filename.c_str(), "rb")) == NULL)
          return;
 
        /* Obtain file length */
        fseek(F, 0, SEEK_END);
        flen = ftell(F);
        rewind(F);
 
        /* Allocate memory and load whole file to memory */
        mem = new BYTE[flen];
        fread(mem, 1, flen, F);
        fclose(F);
 
        /* Get pointer with memory bulk
           to special pointer */
        ptr = mem;

        /* Signature */
        Sign = *(DWORD *)ptr;
        ptr += 4;
        if (Sign != *(DWORD *)"G3DM")
        {
          delete[] mem;
          return;
        }

        /* Get count of prims, materials and textures */
        NumOfPrims = *(DWORD *)ptr;
        ptr += 4;
        NumOfMaterials = *(DWORD *)ptr;
        ptr += 4;
        NumOfTextures = *(DWORD *)ptr;
        ptr += 4;

        /* Load primitives */
        for (p = 0; p < NumOfPrims; p++)
        {
          DWORD NumOfVertexes;
          DWORD NumOfFaceIndexes;
          DWORD MtlNo;
          vertex *V;
          INT *Ind;

          NumOfVertexes = *(DWORD *)ptr;
          ptr += 4;
          NumOfFaceIndexes = *(DWORD *)ptr;
          ptr += 4;
          MtlNo = *(DWORD *)ptr;
          ptr += 4;

          V = (vertex *)ptr;
          ptr += sizeof(vertex) * NumOfVertexes;
          Ind = (INT *)ptr;
          ptr += sizeof(INT) * NumOfFaceIndexes;

          std::vector<vertex> VArr;
          std::vector<INT> IArr;

          for (INT i = 0; i < NumOfVertexes; ++i)
            VArr.push_back(V[i]);
          for (INT i = 0; i < NumOfFaceIndexes; ++i)
            IArr.push_back(Ind[i]);

          prim Pr = prim(VArr, IArr);
          Pr.Surf = surface("Gold");

          Prims.push_back(std::move(Pr));
          Prims[p].MtlNo = MtlManager.MtlCount + MtlNo;
        }

        /* Load materials */
        for (m = 0; m < NumOfMaterials; m++)
        {
          struct MaterialStruct
          {
            CHAR Name[300];         // Material name
            
            // Illumination coefficients
            fvec3 Ka, Kd, Ks;       // Ambient, diffuse, specular coefficients
            FLT Ph;                 // Phong power coefficient – shininess 
            FLT Trans;              // Transparency factor
            DWORD Tex[8];           // Texture references 
                                    // (8 time: texture number in G3DM file, -1 if no texture)
            
            // Shader information
            CHAR ShaderString[300]; // Additional shader information 
            DWORD Shader;           // Shader number (uses after load into memory)
          } *fmat;
          surface mtl;

          fmat = (MaterialStruct *)ptr;
          ptr += sizeof(*fmat);
          mtl.Ka = ConvertFVtoDV3(fmat->Ka);
          mtl.Kd = ConvertFVtoDV3(fmat->Kd);
          mtl.Ks = ConvertFVtoDV3(fmat->Ks);
          mtl.Ph = fmat->Ph;
          mtl.Kt = fmat->Trans;
          mtl.Kr = 0.2;
          for (t = 0; t < 8; t++)
            mtl.TexNum[t] = fmat->Tex[t] == -1 ? -1 : TexManager.TexCount + fmat->Tex[t];
          MtlManager.AddMaterial(mtl);
        }

        /* Load textures */
        for (t = 0; t < NumOfTextures; t++)
        {
          DWORD W, H, C;
 
          ptr += 300;
          W = *(DWORD *)ptr;
          ptr += 4;
          H = *(DWORD *)ptr;
          ptr += 4;
          C = *(DWORD *)ptr;
          ptr += 4;
          TexManager.AddTexture(W, H, C, (const VOID *)ptr);

#if 0
          FILE *F = fopen(std::format("{}.g32", t).c_str(), "wb");

          if (F != nullptr)
          {
            fwrite(&W, 2, 1, F);
            fwrite(&H, 2, 1, F);
            fwrite(ptr, C, W * H, F);
            fclose(F);
          }
#endif

          ptr += W * H * C;
        }

        delete[] mem;

        if (NumOfMaterials > 0)
          for (auto &i : Prims)
            i.UpdateSurf();
      } /* End of 'g3dm' function */

      /* Default destructor */
      ~g3dm( VOID ) override
      {
      } /* End of '~g3dm' function' */

      /* Get intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersection structure:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) status of success intersection.
       */
      BOOL Intersect( const ray &R, intr *Intr )
      {
        DBL t = -1;
        intr tmp;

        for (auto &i : Prims)
          if (prim_storage::BBIsIntersected(R, i.MinBB, i.MaxBB))
            if (i.Intersect(R, &tmp) && (tmp.T < t || t == -1))
              *Intr = tmp, t = tmp.T;

        Intr->V[0] = R(Intr->T);

        return t == -1 ? FALSE : TRUE;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) override
      {
        Intr->Shp->GetNormal(Intr);
      } /* End of 'GetNormal' function */

      /* Get all intersects function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - list with intersections:
       *       intr_list &Il;
       * RETURNS:
       *   (INT) count of intersections.
       */
      INT AllIntersect( const ray &R, intr_list &Il ) override
      {
        intr_list All;
        INT count = 0;

        for (auto &i : Prims)
          if (prim_storage::BBIsIntersected(R, i.MinBB, i.MaxBB))
            count += i.AllIntersect(R, All);

        // Sort array by distance to intersection
        if (count)
          std::qsort(Il.data(), count, sizeof(intr), []( VOID const *A1, VOID const *A2 ) -> INT
            {
              intr const *E1 = reinterpret_cast<intr const *>(A1);
              intr const *E2 = reinterpret_cast<intr const *>(A2);

              return 
                (E1->T < E2->T) ? -1 :
                (E1->T > E2->T) ? 1 :
                0;
            });

        return count;
      } /* End of 'AllIntersect' function */

      /* Get information about insiding location point in shape function.
       * ARGUMENTS:
       *   - point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) true - if point inside, else false.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        return FALSE;
      } /* End of 'IsInside' function */

      /* Get information about intersect ray of shape function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       * RETURNS:
       *   (BOOL) true - if ray intersect, else false.
       */
      BOOL IsIntersect( const ray &R ) override
      {
        intr tmp;

        for (auto &i : Prims)
          if (prim_storage::BBIsIntersected(R, i.MinBB, i.MaxBB))
            if (i.Intersect(R, &tmp))
              return TRUE;

        return FALSE;
      } /* End of 'IsIntersect' function */

    }; /* End of 'g3dm' function */

  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__g3dm_h_

/* END OF 'g3dm.h' FILE */
