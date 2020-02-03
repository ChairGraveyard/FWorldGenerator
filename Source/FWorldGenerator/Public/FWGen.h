// This file is part of the FWorldGenenerator.
// Copyright Aleksandr "Flone" Tretyakov (github.com/Flone-dnb).
// Licensed under the ZLib license.
// Refer to the LICENSE file included.

#pragma once

// UE
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

// STL
#include <vector>
#include <random>

#include "FWGen.generated.h"


class UStaticMeshComponent;

#if WITH_EDITOR
class UBoxComponent;
#endif // WITH_EDITOR


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

class FWGenChunkMap;
class FWGenChunk;


UCLASS()
class FWORLDGENERATOR_API AFWGen : public AActor
{
	GENERATED_BODY()
	
public:	
	AFWGen();

	~AFWGen();


	UFUNCTION(BlueprintCallable, Category = "FWorldGenerator")
		void          GenerateWorld();


	// "Set" functions
		
		// Chunks

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Chunks")
			bool SetChunkPieceRowCount(int32 NewChunkPieceRowCount);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Chunks")
			bool SetChunkPieceColumnCount(int32 NewChunkPieceColumnCount);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Chunks")
			bool SetChunkPieceSizeX(float NewChunkPieceSizeX);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Chunks")
			bool SetChunkPieceSizeY(float NewChunkPieceSizeY);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Chunks")
			bool SetViewDistance(int32 NewViewDistance);


		// Generation

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Generation")
			bool SetGenerationFrequency(float NewGenerationFrequency);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Generation")
			bool SetGenerationOctaves(int32 NewGenerationOctaves);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Generation")
			bool SetGenerationSeed(int32 NewGenerationSeed);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Generation")
			bool SetGenerationMaxZFromActorZ(float NewGenerationMaxZFromActorZ);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Generation")
			void SetInvertWorld(bool InvertWorld);


		// World

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | World")
			bool SetWorldSize(int32 NewWorldSize);


		// Ground

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground")
			void SetGroundMaterial(UMaterialInterface* NewGroundMaterial);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground")
			bool SetFirstMaterialMaxRelativeHeight(float NewFirstMaterialMaxRelativeHeight);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground")
			bool SetSecondMaterialMaxRelativeHeight(float NewSecondMaterialMaxRelativeHeight);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground")
			bool SetMaterialHeightMaxDeviation(float NewMaterialHeightMaxDeviation);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground Material Blend")
			bool SetFirstMaterialOnOtherProbability(float FirstOnSecond, float FirstOnThird);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground Material Blend")
			bool SetSecondMaterialOnOtherProbability(float SecondOnFirst, float SecondOnThird);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground Material Blend")
			bool SetThirdMaterialOnOtherProbability(float ThirdOnFirst, float ThirdOnSecond);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Ground Material Blend")
			bool SetIncreasedMaterialBlendProbability(float NewIncreasedMaterialBlendProbability);


		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Additional Steps")
			void SetApplyGroundMaterialBlend(bool bApply);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Additional Steps")
			void SetApplySlopeDependentBlend(bool bApply);


		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Slope Dependent Blend")
			bool SetMinSlopeHeightMultiplier(float NewMinSlopeHeightMultiplier);



		// Water

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Water")
			void SetCreateWater(bool CreateWater);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Water")
			void SetSecondMaterialUnderWater(bool NewSecondMaterialUnderWater);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Water")
			bool SetZWaterLevelInWorld(float NewZWaterLevelInWorld);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Water")
			bool SetWaterSize(int32 NewWaterSize);

		UFUNCTION(BlueprintCallable, Category = "FWorldGenerator | Water")
			void SetWaterMaterial(UMaterialInterface* NewWaterMaterial);


#if WITH_EDITOR
	virtual void  PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void  PostEditMove          (bool bFinished);
#endif // WITH_EDITOR



#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
		bool  ComplexPreview = false;
#endif // WITH_EDITOR

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunks")
		int32 ChunkPieceRowCount = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunks")
		int32 ChunkPieceColumnCount = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunks")
		float ChunkPieceSizeX = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunks")
		float ChunkPieceSizeY = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunks")
		int32 ViewDistance = 1;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
		float GenerationFrequency = 0.65f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
		int32 GenerationOctaves = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
		int32 GenerationSeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
		float GenerationMaxZFromActorZ = 50000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
		bool  InvertWorld = false;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
		int32 WorldSize = 0;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
		UMaterialInterface* GroundMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
		float FirstMaterialMaxRelativeHeight = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
		float SecondMaterialMaxRelativeHeight = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
		float MaterialHeightMaxDeviation = 0.08f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additional Steps")
		bool ApplyGroundMaterialBlend = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additional Steps")
		bool ApplySlopeDependentBlend = true;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float FirstMaterialOnSecondProbability = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float FirstMaterialOnThirdProbability  = 0.002f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float SecondMaterialOnFirstProbability = 0.008f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float SecondMaterialOnThirdProbability = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float ThirdMaterialOnFirstProbability  = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float ThirdMaterialOnSecondProbability = 0.004f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Material Blend")
		float IncreasedMaterialBlendProbability = 0.16f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slope Dependent Blend")
		float MinSlopeHeightMultiplier = 0.006f;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
		bool  CreateWater = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
		bool  SecondMaterialUnderWater = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
		float ZWaterLevelInWorld = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
		int32 WaterSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
		UMaterialInterface* WaterMaterial;


protected:

	virtual void BeginPlay() override;



	// --------------------------------------------------------------



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		USceneComponent* pRootNode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* WaterPlane;

#if WITH_EDITOR
	UPROPERTY()
		UBoxComponent* PreviewPlane;
#endif // WITH_EDITOR


private:

	FWGenChunk* generateChunk(long long iX, long long iY, int32 iSectionIndex);
	void generateSeed();
	float pickVertexMaterial(double height, bool bApplyRND, std::uniform_real_distribution<float>* pUrd, std::mt19937_64* pRnd, float* pfLayerTypeWithoutRnd = nullptr);
	void blendWorldMaterialsMore();
	void applySlopeDependentBlend();

	bool areEqual(float a, float b, float eps);

	void compareHeightDifference(FWGenChunk* pChunk, std::vector<bool>& vProcessedVertices, float& fCurrentZ, size_t iCompareToIndex, float& fSteepSlopeMinHeightDiff);

#if WITH_EDITOR
	void refreshPreview();
#endif // WITH_EDITOR

	UPROPERTY()
	UProceduralMeshComponent* pProcMeshComponent;


	FWGenChunkMap*            pChunkMap;


	int32                     iGeneratedSeed;


	bool                      bWorldCreated;
};


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------



class FWGenChunk
{
public:
	FWGenChunk(long long iX, long long iY, int32 iSectionIndex)
	{
		pMeshSection = nullptr;

		this->iX = iX;
		this->iY = iY;

		this->iSectionIndex = iSectionIndex;
	}

	void clearChunk()
	{
		vVertices     .Empty();
		vTriangles    .Empty();
		vNormals      .Empty();
		vUV0          .Empty();
		vVertexColors .Empty();
		vTangents     .Empty();

		pMeshSection->Reset();
	}

	int32 getX() const
	{
		return iX;
	}

	int32 getY() const
	{
		return iY;
	}

	void setMeshSection(FProcMeshSection* pMeshSection)
	{
		this->pMeshSection  = pMeshSection;
	}


	UPROPERTY()
	FProcMeshSection* pMeshSection;


	TArray<FProcMeshTangent>  vTangents;
	TArray<FLinearColor>      vVertexColors;
	TArray<FVector>           vVertices;
	TArray<int32>             vTriangles;
	TArray<FVector>           vNormals;
	TArray<FVector2D>         vUV0;
	std::vector<int32>        vLayerIndex;

	size_t                    iMaxZVertexIndex;

private:


	long long                 iX;
	long long                 iY;


	int32                     iSectionIndex;
};


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------


class FWGenChunkMap
{
public:

	void addChunk(FWGenChunk* pChunk)
	{
		vChunks.push_back(pChunk);
	}

	void clearChunks()
	{
		for (size_t i = 0; i < vChunks.size(); i++)
		{
			vChunks[i]->clearChunk();
		}
	}

	void clearWorld(UProceduralMeshComponent* pProcMeshComponent)
	{
		for (size_t i = 0; i < vChunks.size(); i++)
		{
			delete vChunks[i];
		}

		vChunks.clear();

		pProcMeshComponent->ClearAllMeshSections();
	}

	FWGenChunk* getLastChunk() const
	{
		return vChunks.back();
	}

	~FWGenChunkMap()
	{
		for (size_t i = 0; i < vChunks.size(); i++)
		{
			delete vChunks[i];
		}
	}

	std::vector<FWGenChunk*> vChunks;
};