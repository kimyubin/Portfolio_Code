﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"EnochFreeLancerAct.h"
#include<vector>
#include<functional>
#include<memory>

using namespace std;

class FLMeleeAttack : public FreeLancerAct
{
public:
	void _End();
	void _Begin();
	int target;
};