///
/// \file Targets.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Targets.h"
#include <fstream>
#include <iostream>

void initialiseTargets()
{
	string targetDirectory = "..//data//targets//";
	string revIndexFile = targetDirectory + "targets_rev_index_";
	ifstream fTargets(targetDirectory + "targets_ordered.txt");
	uint targetIndex = 0;
	while(!fTargets.eof())
	{
		fTargets >> targets[targetIndex].x >> targets[targetIndex].y >> targets[targetIndex].theta;
		targetIndex++;
		if(targetIndex == NUM_TARGETS)
			break;
	}
	fTargets.close();

	ifstream fSymmetricTargets(targetDirectory + "symmetric_targets.txt");
	targetIndex = 0;
	while(!fSymmetricTargets.eof())
	{
		fSymmetricTargets >> symmetricIndices[targetIndex];
		symmetricIndices[targetIndex]; // indices start at 1
		targetIndex++;
		if(targetIndex == NUM_TARGETS)
			break;
	}
	fSymmetricTargets.close();

	for(uint subjectNumber = 0; subjectNumber < NUM_SUBJECTS; subjectNumber++)
	{
		ifstream fSubject(targetDirectory + "targets_rev_index_" + intToString(subjectNumber + 1) + ".txt");
		targetIndex = 0;
		while(!fSubject.eof())
		{
			uint index1, index2;
			fSubject >> index1 >> index2;
			sequenceNumber[subjectNumber][targetIndex] = index1; // indices start at 0
			sequenceNumberAlt[subjectNumber][targetIndex] = index2; // indices start at 0
			
			if(index1 > 0)
				targetNumber[subjectNumber][index1 - 1] = targetIndex + 1; // target #s start at 1
			if(index2 > 0)
				targetNumber[subjectNumber][index2 - 1] = targetIndex + 1;

			targetIndex++;
			if(targetIndex == NUM_TARGETS)
				break;
		}
		fSubject.close();
	}
}

vector<uint> getSequenceNumbers(uint subjectNumber, uint targetNumber)
{
	vector<uint> indices;
	if(subjectNumber > 0 && subjectNumber <= NUM_SUBJECTS && targetNumber > 0 && targetNumber <= NUM_TARGETS)
	{
		uint index1 = sequenceNumber[subjectNumber - 1][targetNumber - 1];
		uint index2 = sequenceNumberAlt[subjectNumber - 1][targetNumber - 1];
		if(index1 > 0)
			indices.push_back(index1);
		if(index2 > 0)
			indices.push_back(index2); // 0 isn't a valid index
	}
	else
	{
		cerr << "getSequenceNumbers(): Subject # or Target # out of range!" << endl;
	}
	return indices;
}

uint getTargetNumber(uint subjectNumber, uint sequenceNumber)
{
	uint index = 0; // invalid index
	if(subjectNumber > 0 && subjectNumber <= NUM_SUBJECTS && sequenceNumber > 0 && sequenceNumber <= NUM_SEQUENCES)
	{
		index = targetNumber[subjectNumber - 1][sequenceNumber - 1];
	}
	else
	{
		cerr << "getTargetNumber(): Subject # or Sequence # out of range!" << endl;
	}
	return index;
}

Target getTarget(uint targetNumber)
{
	if(targetNumber > 0 && targetNumber <= NUM_TARGETS)
		return targets[targetNumber - 1];
	else 
	{
		cerr << "getTarget(): target # out of range!" << endl;
		return Target();
	}
}

Target getTargetFromSequenceNum(uint subjectNumber, uint sequenceNumber)
{
	return getTarget(getTargetNumber(subjectNumber, sequenceNumber));
}

uint getSymmetricTarget(uint targetNumber)
{
	if(targetNumber > 0 && targetNumber <= NUM_TARGETS)
		return symmetricIndices[targetNumber - 1];
	else 
	{
		cerr << "getSymmetricTarget(): target # out of range!" << endl;
		return 0;
	}
}