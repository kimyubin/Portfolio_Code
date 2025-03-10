// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Interfaces/Interface_CollisionDataProvider.h"
#include "Components/MeshComponent.h"
#include "AsyncProceduralMeshComponent.generated.h"

struct FKConvexElem;

class FPrimitiveSceneProxy;

/**
*	Component that allows you to specify custom triangle mesh geometry
*	Beware! This feature is experimental and may be substantially changed in future releases.
*/
UCLASS(hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class KKUMIGI_API UAsyncProceduralMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_BODY()
public:

	UAsyncProceduralMeshComponent(const FObjectInitializer& ObjectInitializer);

	/**
	 *	Create/replace a section for this procedural mesh component.
	 *	This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead.
	 *	@param	SectionIndex		Index of the section to create or replace.
	 *	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
	 *	@param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3.
	 *	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DeprecatedFunction, DeprecationMessage = "This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead.", DisplayName = "Create Mesh Section FColor", AutoCreateRefTerm = "Normals,UV0,VertexColors,Tangents"))
	void CreateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision)
	{
		TArray<FVector2D> EmptyArray;
		CreateMeshSection(SectionIndex, Vertices, Triangles, Normals, UV0, EmptyArray, EmptyArray, EmptyArray, VertexColors, Tangents, bCreateCollision);
	}

	void CreateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision);

	/**
	 *	Create/replace a section for this procedural mesh component.
	 *	@param	SectionIndex		Index of the section to create or replace.
	 *	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
	 *	@param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3.
	 *	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
	 *	@param	bSRGBConversion		Whether to do sRGB conversion when converting FLinearColor to FColor
	 */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DisplayName = "Create Mesh Section", AutoCreateRefTerm = "Normals,UV0,UV1,UV2,UV3,VertexColors,Tangents", AdvancedDisplay = "UV1,UV2,UV3"))
	void CreateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3,
		const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision, UPARAM(DisplayName = "SRGB Conversion") bool bSRGBConversion = false);

	void CreateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision, bool bSRGBConversion = false)
	{
		TArray<FVector2D> EmptyArray;
		CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UV0, EmptyArray, EmptyArray, EmptyArray, VertexColors, Tangents, bCreateCollision, bSRGBConversion);
	}

	/**
	 *	Updates a section of this procedural mesh component. This is faster than CreateMeshSection, but does not let you change topology. Collision info is also updated.
	 *	This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead.
	 *	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
	 *	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DeprecatedFunction, DeprecationMessage = "This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Update Mesh Section' function which uses LinearColor instead.", DisplayName = "Update Mesh Section FColor", AutoCreateRefTerm = "Normals,UV0,VertexColors,Tangents"))
	void UpdateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents)
	{
		TArray<FVector2D> EmptyArray;
		UpdateMeshSection(SectionIndex, Vertices, Normals, UV0, EmptyArray, EmptyArray, EmptyArray, VertexColors, Tangents);
	}

	void UpdateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents);

	/**
	 *	Updates a section of this procedural mesh component. This is faster than CreateMeshSection, but does not let you change topology. Collision info is also updated.
	 *	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
	 *	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
	 *	@param	bSRGBConversion		Whether to do sRGB conversion when converting FLinearColor to FColor
	 */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DisplayName = "Update Mesh Section", AutoCreateRefTerm = "Normals,UV0,UV1,UV2,UV3,VertexColors,Tangents", AdvancedDisplay = "UV1,UV2,UV3"))
	void UpdateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3,
		const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, UPARAM(DisplayName = "SRGB Conversion") bool bSRGBConversion = true);

	void UpdateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bSRGBConversion = true)
	{
		TArray<FVector2D> EmptyArray;
		UpdateMeshSection_LinearColor(SectionIndex, Vertices, Normals, UV0, EmptyArray, EmptyArray, EmptyArray, VertexColors, Tangents, bSRGBConversion);
	}

	/** Clear a section of the procedural mesh. Other sections do not change index. */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void ClearMeshSection(int32 SectionIndex);

	/** Clear all mesh sections and reset to empty state */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void ClearAllMeshSections();

	/** Control visibility of a particular section */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void SetMeshSectionVisible(int32 SectionIndex, bool bNewVisibility);

	/** Returns whether a particular section is currently visible */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	bool IsMeshSectionVisible(int32 SectionIndex) const;

	/** Returns number of sections currently created for this component */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	int32 GetNumSections() const;

	/** Add simple collision convex to this component */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void AddCollisionConvexMesh(TArray<FVector> ConvexVerts);

	/** Remove collision meshes from this component */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void ClearCollisionConvexMeshes();

	/** Function to replace _all_ simple collision in one go */
	void SetCollisionConvexMeshes(const TArray< TArray<FVector> >& ConvexMeshes);

	//~ Begin Interface_CollisionDataProvider Interface
	virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;
	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	virtual bool WantsNegXTriMesh() override{ return false; }
	//~ End Interface_CollisionDataProvider Interface

	/** 
	 *	Controls whether the complex (Per poly) geometry should be treated as 'simple' collision. 
	 *	Should be set to false if this component is going to be given simple collision and simulated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Procedural Mesh")
	bool bUseComplexAsSimpleCollision;

	/**
	*	Controls whether the physics cooking should be done off the game thread. This should be used when collision geometry doesn't have to be immediately up to date (For example streaming in far away objects)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Procedural Mesh")
	bool bUseAsyncCooking;

	/** Collision data */
	UPROPERTY(Instanced)
	TObjectPtr<class UBodySetup> AsyncProcMeshBodySetup;

	/** 
	 *	Get pointer to internal data for one section of this procedural mesh component. 
	 *	Note that pointer will becomes invalid if sections are added or removed.
	 */
	FProcMeshSection* GetAsyncProcMeshSection(int32 SectionIndex);

	/** Replace a section with new section geometry */
	void SetAsyncProcMeshSection(int32 SectionIndex, const FProcMeshSection& Section);
	/** Replace a section with new section geometry */
	void SetAsyncProcMeshSection(int32 SectionIndex, FProcMeshSection&& Section);
	
	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual class UBodySetup* GetBodySetup() override;
	virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;
	//~ End UPrimitiveComponent Interface.

	//~ Begin UMeshComponent Interface.
	virtual int32 GetNumMaterials() const override;
	//~ End UMeshComponent Interface.

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface.

	//~ Begin USceneComponent Interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	//~ Begin USceneComponent Interface.

private:

	/** Update LocalBounds member from the local box of each section */
	void UpdateLocalBounds();
	/** Ensure AsyncProcMeshBodySetup is allocated and configured */
	void CreateAsyncProcMeshBodySetup();
	/** Mark collision data as dirty, and re-create on instance if necessary */
	void UpdateCollision();
	/** Once async physics cook is done, create needed state */
	void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);

	/** Helper to create new body setup objects */
	UBodySetup* CreateBodySetupHelper();

	/** Array of sections of mesh */
	UPROPERTY()
	TArray<FProcMeshSection> AsyncProcMeshSections;

	/** Convex shapes used for simple collision */
	UPROPERTY()
	TArray<FKConvexElem> CollisionConvexElems;

	/** Local space bounds of mesh */
	UPROPERTY()
	FBoxSphereBounds LocalBounds;
	
	/** Queue for async body setups that are being cooked */
	UPROPERTY(transient)
	TArray<TObjectPtr<UBodySetup>> AsyncBodySetupQueue;

	friend class FAsyncProceduralMeshSceneProxy;
};



#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_2
#include "CoreMinimal.h"
#include "PhysicsEngine/ConvexElem.h"
#endif
