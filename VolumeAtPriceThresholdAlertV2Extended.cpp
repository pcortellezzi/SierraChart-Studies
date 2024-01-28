#include "sierrachart.h"

SCDLLName("Volume At Price Threshold Alert V2 Extended")

/*==========================================================================*/
SCSFExport scsf_VolumeAtPriceThresholdAlertV2Extended(SCStudyInterfaceRef sc)
{
	SCSubgraphRef Subgraph_ExtensionLineProperties = sc.Subgraph[SC_SUBGRAPHS_AVAILABLE - 1];
	SCSubgraphRef Subgraph_CountOfAlerts = sc.Subgraph[SC_SUBGRAPHS_AVAILABLE - 2];

	int AdjacentAlertsHighlightSubgraphStartingNumber = SC_SUBGRAPHS_AVAILABLE - 12;

	SCInputRef Input_ComparisonMethod = sc.Input[0];
	SCInputRef Input_VolumeThreshold = sc.Input[1];
	SCInputRef Input_AlertNumber = sc.Input[2];
	SCInputRef Input_DrawExtensionLines = sc.Input[3];
	SCInputRef Input_DrawExtensionLinesWithTransparentRange = sc.Input[4];
	SCInputRef Input_PercentageThreshold = sc.Input[5];
	SCInputRef Input_AdditionalVolumeThreshold = sc.Input[6];
	SCInputRef Input_AllowZeroValueCompares = sc.Input[7];
	SCInputRef Input_DivideByZeroAction = sc.Input[8];
	SCInputRef Input_HighlightAdjacentAlertsGroupSize = sc.Input[9];
	SCInputRef Input_DrawExtensionLinesUntilEndOfChart = sc.Input[10];
	SCInputRef Input_NumberOfDaysToCalculate = sc.Input[11];
	SCInputRef Input_Version = sc.Input[12];

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults
		sc.GraphName = "Volume At Price Threshold Alert V2";

		sc.GraphRegion = 0;		
		sc.AutoLoop = 0;//Manual looping
		sc.ValueFormat = sc.BaseGraphValueFormat;		

		sc.MaintainVolumeAtPriceData = 1;  // true
	
		for (int SubgraphIndex = 0; SubgraphIndex < SC_SUBGRAPHS_AVAILABLE - 13; ++SubgraphIndex)
		{
			SCString SubgraphName;
			SubgraphName.Format("Trigger %d", SubgraphIndex);

			sc.Subgraph[SubgraphIndex].Name = SubgraphName;
			sc.Subgraph[SubgraphIndex].PrimaryColor = RGB(255, 128, 0);
			sc.Subgraph[SubgraphIndex].DrawStyle = DRAWSTYLE_SQUARE_OFFSET_LEFT_FOR_CANDLESTICK;
			sc.Subgraph[SubgraphIndex].LineWidth = 8;
			sc.Subgraph[SubgraphIndex].DrawZeros = 0;
			sc.Subgraph[SubgraphIndex].DisplayNameValueInWindowsFlags = 0;
		}

		Subgraph_CountOfAlerts.Name = "Count of Alerts";
		Subgraph_CountOfAlerts.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_CountOfAlerts.PrimaryColor = RGB(0, 255, 0);
		Subgraph_CountOfAlerts.DrawZeros = 1;

		for (int SubgraphIndex = 0; SubgraphIndex < 10; ++SubgraphIndex)
		{
			SCString SubgraphName;
			SubgraphDrawStyles AdjacentAlertsDrawStyle;
			if (SubgraphIndex % 2 == 0)
			{
				SubgraphName.Format("Adjacent Alert Highlight Bottom %d", static_cast<int>(SubgraphIndex / 2) + 1);
				AdjacentAlertsDrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_TOP_FOR_CANDLESTICK;
			}
			else
			{
				SubgraphName.Format("Adjacent Alert Highlight Top %d", static_cast<int>(SubgraphIndex / 2) + 1);
				AdjacentAlertsDrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_BOTTOM_FOR_CANDLESTICK;
			}

			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].Name = SubgraphName;
			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].PrimaryColor = RGB(255, 255, 0);
			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DrawStyle = AdjacentAlertsDrawStyle;
			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].LineWidth = 8;
			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DisplayNameValueInWindowsFlags = 0;
		}

		Subgraph_ExtensionLineProperties.Name = "Extension Line Properties";
		Subgraph_ExtensionLineProperties.DrawStyle = DRAWSTYLE_SUBGRAPH_NAME_AND_VALUE_LABELS_ONLY;
		Subgraph_ExtensionLineProperties.LineWidth = 1;
		Subgraph_ExtensionLineProperties.PrimaryColor =  RGB (255, 0, 255);
		Subgraph_ExtensionLineProperties.DrawZeros = false;
		Subgraph_ExtensionLineProperties.DisplayNameValueInWindowsFlags = 0;

		Input_ComparisonMethod.Name = "Comparison Method";
		Input_ComparisonMethod.SetCustomInputStrings("Bid Volume;Ask Volume;Total Volume;Number of Trades;Ask Volume Bid Volume Difference;Ask Volume Bid Volume Diagonal Difference;Ask Volume Bid Volume Ratio;Ask Volume Bid Volume Diagonal Ratio;Bid Volume and Ask Volume Separately");
		Input_ComparisonMethod.SetCustomInputIndex(2);

		Input_VolumeThreshold.Name = "Volume Threshold";
		Input_VolumeThreshold.SetInt(100);

		Input_AlertNumber.Name = "Volume Alert Number";
		Input_AlertNumber.SetAlertSoundNumber(0);

		Input_DrawExtensionLines.Name = "Draw Extension Lines";
//		Input_DrawExtensionLines.SetYesNo(false);
		Input_DrawExtensionLines.SetCustomInputStrings("None;All Alerts;Lowest Price in Adjacent Alerts;Highest Price in Adjacent Alerts;All Prices in Adjacent Alerts");
		Input_DrawExtensionLines.SetCustomInputIndex(0);

		Input_DrawExtensionLinesWithTransparentRange.Name = "Draw Extension Lines With Transparent Range";
		Input_DrawExtensionLinesWithTransparentRange.SetYesNo(false);

		Input_PercentageThreshold.Name = "Percentage Threshold";
		Input_PercentageThreshold.SetInt(150);
		
		Input_AdditionalVolumeThreshold.Name = "Additional Volume Threshold";
		Input_AdditionalVolumeThreshold.SetInt(100);

		Input_AllowZeroValueCompares.Name = "Enable Zero Bid/Ask Compares";
		Input_AllowZeroValueCompares.SetYesNo(0);

		Input_DivideByZeroAction.Name = "Zero Value Compare Action";
		Input_DivideByZeroAction.SetCustomInputStrings("Set 0 to 1;Set Percentage to +/- 1000%");
		Input_DivideByZeroAction.SetCustomInputIndex(0);

		Input_HighlightAdjacentAlertsGroupSize.Name = "Highlight Adjacent Alerts Minimum Group Size";
		Input_HighlightAdjacentAlertsGroupSize.SetInt(0);

		Input_DrawExtensionLinesUntilEndOfChart.Name = "Draw Extension Lines until End of Chart";
		Input_DrawExtensionLinesUntilEndOfChart.SetYesNo(false);

		Input_NumberOfDaysToCalculate.Name = "Number of Days to Calculate";
		Input_NumberOfDaysToCalculate.SetInt(30);
		Input_NumberOfDaysToCalculate.SetIntLimits(1, 10000);

		Input_Version.SetInt(2);

		sc.ValueFormat = VALUEFORMAT_INHERITED;

		return;
	}

	const int TransparencyLevel = sc.GetChartStudyTransparencyLevel(sc.ChartNumber, sc.StudyGraphInstanceID);

	if (Input_Version.GetInt() < 1)
	{
		Input_Version.SetInt(1);
		Input_NumberOfDaysToCalculate.SetInt(30);
	}

	if (Input_Version.GetInt() < 2)
	{
		Input_Version.SetInt(2);
		if (Input_DrawExtensionLines.GetYesNo() == false)
			Input_DrawExtensionLines.SetCustomInputIndex(0);
		else
			Input_DrawExtensionLines.SetCustomInputIndex(1);
	}
			
	//This is an indication that the volume at price data does not exist
	if (static_cast<int>(sc.VolumeAtPriceForBars->GetNumberOfBars()) < sc.ArraySize)
		return;

	//The Subgraph display properties need to be the same for all Subgraphs. If the properties at Subgraph index 1 are different than at subgraph index 0, then apply Subgraph 0 properties to the rest.

	if (sc.Subgraph[1].PrimaryColor != sc.Subgraph[0].PrimaryColor
		|| sc.Subgraph[1].DrawStyle != sc.Subgraph[0].DrawStyle
		|| sc.Subgraph[1].LineWidth != sc.Subgraph[0].LineWidth
	)
	{
		for (int SubgraphIndex = 1; SubgraphIndex < SC_SUBGRAPHS_AVAILABLE - 13; ++SubgraphIndex)
		{
			sc.Subgraph[SubgraphIndex].PrimaryColor = sc.Subgraph[0].PrimaryColor;
			sc.Subgraph[SubgraphIndex].DrawStyle = sc.Subgraph[0].DrawStyle;
			sc.Subgraph[SubgraphIndex].LineWidth = sc.Subgraph[0].LineWidth;
		}
	}

	SCString AlertMessage;
	bool EnableAlerts = sc.IsFullRecalculation == 0 && !sc.ChartIsDownloadingHistoricalData(sc.ChartNumber);

	if (Input_HighlightAdjacentAlertsGroupSize.GetInt() == 0)
	{
		for (int SubgraphIndex = 0; SubgraphIndex < 10; ++SubgraphIndex)
		{
			sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DrawStyle = DRAWSTYLE_IGNORE;
		}

		if (Input_DrawExtensionLines.GetIndex() > 1)
		{
			Input_DrawExtensionLines.SetCustomInputIndex(1);
		}
	}
	else if (Input_HighlightAdjacentAlertsGroupSize.GetInt() != 0)
	{
		bool AllSetToIgnore = true;
		for (int SubgraphIndex = 0; SubgraphIndex < 10; ++SubgraphIndex)
		{
			if (sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DrawStyle != DRAWSTYLE_IGNORE)
			{
				AllSetToIgnore = false;
				break;
			}
		}

		if (AllSetToIgnore)
		{
			for (int SubgraphIndex = 0; SubgraphIndex < 10; ++SubgraphIndex)
			{
				if (SubgraphIndex % 2 == 0)
				{
					sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_TOP_FOR_CANDLESTICK;
				}
				else
				{
					sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + SubgraphIndex].DrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_BOTTOM_FOR_CANDLESTICK;
				}
			}
		}
	}

	const int HighlightAdjacentAlertsGroupSizeValue = Input_HighlightAdjacentAlertsGroupSize.GetInt();

	SCDateTimeMS StartDateTimeForCalculations = sc.BaseDateTimeIn[sc.ArraySize - 1];
	StartDateTimeForCalculations.SubtractDays(Input_NumberOfDaysToCalculate.GetInt());
	StartDateTimeForCalculations = sc.GetStartOfPeriodForDateTime(StartDateTimeForCalculations, TIME_PERIOD_LENGTH_UNIT_DAYS , 1, 0);

	int LineID = 0;

	for (int BarIndex = sc.UpdateStartIndex; BarIndex < sc.ArraySize; BarIndex++)
	{
		if (sc.BaseDateTimeIn[BarIndex] < StartDateTimeForCalculations)
		{
			continue;
		}

		int AvailableSubgraphIndex = 0;

		Subgraph_CountOfAlerts[BarIndex] = 0;

		bool AdjacentAlertsHaveBottomHighlightAlertPrice = false;
		int AdjacentAlertsHighlightBottomPriceIndex = 0;
		bool AdjacentAlertsGotGroup = false;
		int AdjacentAlertsGroupNumber = -1;
		int AdjacentAlertsCountInGroup = 0;

		//Reset all subgraph values
		for (int SubgraphIndex = 0; SubgraphIndex < SC_SUBGRAPHS_AVAILABLE - 2; ++SubgraphIndex)
			sc.Subgraph[SubgraphIndex].Data[BarIndex] = 0;

		bool GotExtensionLineForGroup = false;
		float AdjacentAlertsHighlightBottomPrice = 0.0f;

		int NumberOfPricesAtBarIndex = sc.VolumeAtPriceForBars->GetSizeAtBarIndex(BarIndex);

		for (int PriceIndex = 0; PriceIndex < NumberOfPricesAtBarIndex; ++PriceIndex)
		{
			s_VolumeAtPriceV2 *p_VolumeAtPrice = NULL;

			if (!sc.VolumeAtPriceForBars->GetVAPElementAtIndex(BarIndex, PriceIndex, &p_VolumeAtPrice))
				continue;

			s_VolumeAtPriceV2 *p_NextVolumeAtPrice = NULL;

			if (PriceIndex < NumberOfPricesAtBarIndex - 1)
			{
				sc.VolumeAtPriceForBars->GetVAPElementAtIndex(BarIndex, PriceIndex + 1, &p_NextVolumeAtPrice);
			}

			float Price = p_VolumeAtPrice->PriceInTicks * sc.TickSize;
			float PriceForExtensionLine = Price;

			// Check if condition has been met
			int ComparisonMethodIndex = Input_ComparisonMethod.GetIndex();
			bool ConditionMet = false;
			unsigned int VolumeThresholdValue = Input_VolumeThreshold.GetInt();
			unsigned int AdditionalVolumeThresholdValue = Input_AdditionalVolumeThreshold.GetInt();

			if (ComparisonMethodIndex == 0)//Bid Volume
			{
				if ((VolumeThresholdValue > 0
					&& p_VolumeAtPrice->BidVolume >= VolumeThresholdValue)
					|| (VolumeThresholdValue == 0 && p_VolumeAtPrice->BidVolume == 0)
					)
					ConditionMet = true;

			}
			else if (ComparisonMethodIndex == 1)//Ask Volume
			{
				if (( VolumeThresholdValue > 0
					&& p_VolumeAtPrice->AskVolume >= VolumeThresholdValue)
					|| (VolumeThresholdValue == 0 && p_VolumeAtPrice->AskVolume == 0)
					)
					ConditionMet = true;
			}
			else if (ComparisonMethodIndex == 2)//Total Volume
			{
				if ((VolumeThresholdValue > 0
					&& p_VolumeAtPrice->Volume >= VolumeThresholdValue)
					|| (VolumeThresholdValue == 0 && p_VolumeAtPrice->Volume == 0)
					)
					ConditionMet = true;
			}
			else if (ComparisonMethodIndex == 3)//Number of Trades
			{
				if ((VolumeThresholdValue > 0
					&& p_VolumeAtPrice->NumberOfTrades >= VolumeThresholdValue)
					|| (VolumeThresholdValue == 0 && p_VolumeAtPrice->NumberOfTrades == 0)
					)
					ConditionMet = true;
			}
			else if (ComparisonMethodIndex == 4)//Ask Volume Bid Volume Difference
			{
				int AskVolumeBidVolumeDifference = p_VolumeAtPrice->AskVolume - p_VolumeAtPrice->BidVolume;

				int VolumeThresholdSigned = Input_VolumeThreshold.GetInt();

				if (AskVolumeBidVolumeDifference > 0 && VolumeThresholdSigned > 0 && AskVolumeBidVolumeDifference >= VolumeThresholdSigned)
					ConditionMet = true;
				else if (AskVolumeBidVolumeDifference < 0 && VolumeThresholdSigned < 0 && AskVolumeBidVolumeDifference <= VolumeThresholdSigned)
					ConditionMet = true;

			}
			else if (ComparisonMethodIndex == 5)//Ask Volume Bid Volume Diagonal Difference
			{
				int AskVolumeBidVolumeDifference = 0;

				if (p_NextVolumeAtPrice != NULL)
				{
					AskVolumeBidVolumeDifference = p_NextVolumeAtPrice->AskVolume - p_VolumeAtPrice->BidVolume;
					if (p_NextVolumeAtPrice->AskVolume > p_VolumeAtPrice->BidVolume)
						PriceForExtensionLine = p_NextVolumeAtPrice->PriceInTicks * sc.TickSize;
				}

				int VolumeThresholdSigned = Input_VolumeThreshold.GetInt();

				if (AskVolumeBidVolumeDifference > 0 && VolumeThresholdSigned > 0 && AskVolumeBidVolumeDifference >= VolumeThresholdSigned)
					ConditionMet = true;
				else if (AskVolumeBidVolumeDifference < 0 && VolumeThresholdSigned < 0 && AskVolumeBidVolumeDifference <= VolumeThresholdSigned)
					ConditionMet = true;

			}
			else if (ComparisonMethodIndex == 6)//Ask Volume Bid Volume Ratio
			{
				bool AllowZeroValueComparesSetting = Input_AllowZeroValueCompares.GetYesNo();
				unsigned int DivideByZeroActionIndex = Input_DivideByZeroAction.GetIndex();
				int AskVolumeBidVolumeRatioPercent = 0;

				if ((p_VolumeAtPrice->AskVolume > 0 && p_VolumeAtPrice->BidVolume > 0) || AllowZeroValueComparesSetting)
				{
					if (p_VolumeAtPrice->AskVolume >= p_VolumeAtPrice->BidVolume)
					{
						if (p_VolumeAtPrice->BidVolume == 0 && DivideByZeroActionIndex == 0)
							AskVolumeBidVolumeRatioPercent = (p_VolumeAtPrice->AskVolume / 1) * 100;
						else if (p_VolumeAtPrice->BidVolume == 0 && DivideByZeroActionIndex == 1)
							AskVolumeBidVolumeRatioPercent = 1000;
						else
							AskVolumeBidVolumeRatioPercent = sc.Round((static_cast<float>(p_VolumeAtPrice->AskVolume) / p_VolumeAtPrice->BidVolume) * 100);
					}
					else
					{
						if (p_VolumeAtPrice->AskVolume == 0 && DivideByZeroActionIndex == 0)
							AskVolumeBidVolumeRatioPercent = (p_VolumeAtPrice->BidVolume / 1) * -100;
						else if (p_VolumeAtPrice->AskVolume == 0 && DivideByZeroActionIndex == 1)
							AskVolumeBidVolumeRatioPercent = -1000;
						else
							AskVolumeBidVolumeRatioPercent = sc.Round((static_cast<float>(p_VolumeAtPrice->BidVolume) / p_VolumeAtPrice->AskVolume) * -100);
					}
				}

				int PercentThresholdSigned = Input_PercentageThreshold.GetInt();

				if (AskVolumeBidVolumeRatioPercent > 0 && PercentThresholdSigned > 0 && AskVolumeBidVolumeRatioPercent >= PercentThresholdSigned)
					ConditionMet = true;
				else if (AskVolumeBidVolumeRatioPercent < 0 && PercentThresholdSigned < 0 && AskVolumeBidVolumeRatioPercent <= PercentThresholdSigned)
					ConditionMet = true;
			}
			else if (ComparisonMethodIndex == 7)//Ask Volume Bid Volume Diagonal Ratio
			{
				bool AllowZeroValueComparesSetting = Input_AllowZeroValueCompares.GetYesNo();
				unsigned int DivideByZeroActionIndex = Input_DivideByZeroAction.GetIndex();
				int AskVolumeBidVolumeRatioPercent = 0;

				if (p_NextVolumeAtPrice != NULL)
				{
					if ((p_NextVolumeAtPrice->AskVolume >= p_VolumeAtPrice->BidVolume) && (p_VolumeAtPrice->BidVolume > 0 || AllowZeroValueComparesSetting))
					{
						if (p_VolumeAtPrice->BidVolume == 0 && DivideByZeroActionIndex == 0)
							AskVolumeBidVolumeRatioPercent = (p_NextVolumeAtPrice->AskVolume / 1) * 100;
						else if (p_VolumeAtPrice->BidVolume == 0 && DivideByZeroActionIndex == 1)
							AskVolumeBidVolumeRatioPercent = 1000;
						else
							AskVolumeBidVolumeRatioPercent = sc.Round((static_cast<float>(p_NextVolumeAtPrice->AskVolume) / p_VolumeAtPrice->BidVolume) * 100);

						Price = p_NextVolumeAtPrice->PriceInTicks * sc.TickSize;
						PriceForExtensionLine = p_NextVolumeAtPrice->PriceInTicks * sc.TickSize;
					}
					else if (p_VolumeAtPrice->BidVolume > p_NextVolumeAtPrice->AskVolume && (p_NextVolumeAtPrice->AskVolume > 0 || AllowZeroValueComparesSetting))
					{
						if (p_NextVolumeAtPrice->AskVolume == 0 && DivideByZeroActionIndex == 0)
							AskVolumeBidVolumeRatioPercent = (p_VolumeAtPrice->BidVolume / 1) * -100;
						else if (p_NextVolumeAtPrice->AskVolume == 0 && DivideByZeroActionIndex == 1)
							AskVolumeBidVolumeRatioPercent = -1000;
						else
							AskVolumeBidVolumeRatioPercent = sc.Round((static_cast<float>(p_VolumeAtPrice->BidVolume) / p_NextVolumeAtPrice->AskVolume) * -100);
					}
				}

				int PercentThresholdSigned = Input_PercentageThreshold.GetInt();

				if (AskVolumeBidVolumeRatioPercent > 0 && PercentThresholdSigned > 0 && AskVolumeBidVolumeRatioPercent >= PercentThresholdSigned)
					ConditionMet = true;
				else if (AskVolumeBidVolumeRatioPercent < 0 && PercentThresholdSigned < 0 && AskVolumeBidVolumeRatioPercent <= PercentThresholdSigned)
					ConditionMet = true;
			}
			else if (ComparisonMethodIndex == 8)//Bid Volume and Ask Volume Separately
			{
				if (
					((VolumeThresholdValue > 0
						&& p_VolumeAtPrice->BidVolume >= VolumeThresholdValue)
						|| (VolumeThresholdValue == 0 && p_VolumeAtPrice->BidVolume == 0))
					&&
					((AdditionalVolumeThresholdValue > 0
						&& p_VolumeAtPrice->AskVolume >= AdditionalVolumeThresholdValue)
						|| (AdditionalVolumeThresholdValue == 0 && p_VolumeAtPrice->AskVolume == 0))
					)
					ConditionMet = true;
			}

			if (ConditionMet)
			{
				Subgraph_CountOfAlerts[BarIndex]++;
				
				// Adjacent Alerts Highlight
				if (HighlightAdjacentAlertsGroupSizeValue > 0 && AdjacentAlertsGroupNumber < 5)
				{
					if (AdjacentAlertsHaveBottomHighlightAlertPrice && PriceIndex != AdjacentAlertsHighlightBottomPriceIndex + AdjacentAlertsCountInGroup)
					{
						AdjacentAlertsHaveBottomHighlightAlertPrice = false;
						AdjacentAlertsCountInGroup = 0;
						if (!AdjacentAlertsGotGroup)
						{
							AdjacentAlertsGroupNumber--;
						}
						AdjacentAlertsGotGroup = false;
						GotExtensionLineForGroup = false;
					}

					if (AdjacentAlertsHaveBottomHighlightAlertPrice == false)
					{
						AdjacentAlertsGroupNumber++;
						sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + AdjacentAlertsGroupNumber * 2].Data[BarIndex] = Price;
						AdjacentAlertsHaveBottomHighlightAlertPrice = true;
						AdjacentAlertsCountInGroup++;
						AdjacentAlertsHighlightBottomPriceIndex = PriceIndex;
						AdjacentAlertsHighlightBottomPrice = Price; // Needed for extension lines
						if (AdjacentAlertsCountInGroup >= HighlightAdjacentAlertsGroupSizeValue)
						{
							sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + AdjacentAlertsGroupNumber * 2 + 1].Data[BarIndex] = Price;
							AdjacentAlertsGotGroup = true;
						}

					}
					else if (AdjacentAlertsHaveBottomHighlightAlertPrice && PriceIndex == AdjacentAlertsHighlightBottomPriceIndex + AdjacentAlertsCountInGroup)
					{
						AdjacentAlertsCountInGroup++;
						if (AdjacentAlertsCountInGroup >= HighlightAdjacentAlertsGroupSizeValue)
						{
							sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + AdjacentAlertsGroupNumber * 2 + 1].Data[BarIndex] = Price;
							AdjacentAlertsGotGroup = true;
						}
					}
					else if (AdjacentAlertsHaveBottomHighlightAlertPrice && !AdjacentAlertsGotGroup)
					{
						AdjacentAlertsCountInGroup = 0;
						AdjacentAlertsHaveBottomHighlightAlertPrice = false;
						sc.Subgraph[AdjacentAlertsHighlightSubgraphStartingNumber + AdjacentAlertsGroupNumber * 2].Data[BarIndex] = 0.0;
						AdjacentAlertsGroupNumber--;
					}
				}

				sc.Subgraph[AvailableSubgraphIndex][BarIndex] = Price;

				// Extension Lines
				if (Input_DrawExtensionLines.GetIndex() == 1 // All Alerts
					&& sc.GetBarHasClosedStatus(BarIndex) == BHCS_BAR_HAS_CLOSED)
				{
					n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
					LineUntilFutureIntersection.StartBarIndex = BarIndex;
					LineUntilFutureIntersection.LineIDForBar = LineID;

					if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
					{
						LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
						LineUntilFutureIntersection.UseLineValue2 = true;
						LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
						LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
					}
					else
						LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

					LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
					LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
					LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;


					if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
						LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

					sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

					LineID++;
				}
				else if (Input_DrawExtensionLines.GetIndex() == 2 // Lowest Price in Adjacent Alerts
					&& AdjacentAlertsGotGroup
					&& !GotExtensionLineForGroup
					&& sc.GetBarHasClosedStatus(BarIndex) == BHCS_BAR_HAS_CLOSED)
				{
					GotExtensionLineForGroup = true;
					PriceForExtensionLine = AdjacentAlertsHighlightBottomPrice;

					n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
					LineUntilFutureIntersection.StartBarIndex = BarIndex;
					LineUntilFutureIntersection.LineIDForBar = LineID;

					if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
					{
						LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
						LineUntilFutureIntersection.UseLineValue2 = true;
						LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
						LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
					}
					else
						LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

					LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
					LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
					LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;

					if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
						LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

					sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

					LineID++;
				}
				else if (Input_DrawExtensionLines.GetIndex() == 3 // Highest Price in Adjacent Alerts
					&& AdjacentAlertsGotGroup
					&& sc.GetBarHasClosedStatus(BarIndex) == BHCS_BAR_HAS_CLOSED)
				{
					if (!GotExtensionLineForGroup) // Have a group, but we don't know if it is the highest point yet
					{
						GotExtensionLineForGroup = true;
						PriceForExtensionLine = Price;

						n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
						LineUntilFutureIntersection.StartBarIndex = BarIndex;
						LineUntilFutureIntersection.LineIDForBar = LineID;

						if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
						{
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
							LineUntilFutureIntersection.UseLineValue2 = true;
							LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
							LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
						}
						else
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

						LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
						LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
						LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;

						if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
							LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

						sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

						LineID++;
					}
					else // Have a new highest point, so remove previous line and add a new one.
					{
						LineID--;
						sc.DeleteLineUntilFutureIntersection(BarIndex, LineID);

						PriceForExtensionLine = Price;

						n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
						LineUntilFutureIntersection.StartBarIndex = BarIndex;
						LineUntilFutureIntersection.LineIDForBar = LineID;

						if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
						{
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
							LineUntilFutureIntersection.UseLineValue2 = true;
							LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
							LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
						}
						else
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

						LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
						LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
						LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;

						if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
							LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

						sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

						LineID++;
					}
				}
				else if (Input_DrawExtensionLines.GetIndex() == 4 // All Prices in Adjacent Alerts
					&& sc.GetBarHasClosedStatus(BarIndex) == BHCS_BAR_HAS_CLOSED)
				{
					if (AdjacentAlertsHaveBottomHighlightAlertPrice && !GotExtensionLineForGroup && AdjacentAlertsGotGroup) // Create lines from bottom to entered adjacent value
					{
						GotExtensionLineForGroup = true;

						for (int PriceIndex = 0; PriceIndex < AdjacentAlertsCountInGroup; PriceIndex++)
						{
							PriceForExtensionLine = AdjacentAlertsHighlightBottomPrice + PriceIndex * sc.TickSize;

							n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
							LineUntilFutureIntersection.StartBarIndex = BarIndex;
							LineUntilFutureIntersection.LineIDForBar = LineID;

							if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
							{
								LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
								LineUntilFutureIntersection.UseLineValue2 = true;
								LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
								LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
							}
							else
								LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

							LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
							LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
							LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;

							if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
								LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

							sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

							LineID++;
						}
					}
					else if (AdjacentAlertsGotGroup && GotExtensionLineForGroup) // Add additional lines that go above the entered adjacent value
					{
						PriceForExtensionLine = Price;

						n_ACSIL::s_LineUntilFutureIntersection LineUntilFutureIntersection;
						LineUntilFutureIntersection.StartBarIndex = BarIndex;
						LineUntilFutureIntersection.LineIDForBar = LineID;

						if (Input_DrawExtensionLinesWithTransparentRange.GetYesNo())
						{
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine + sc.TickSize * 0.5f;
							LineUntilFutureIntersection.UseLineValue2 = true;
							LineUntilFutureIntersection.LineValue2ForRange = PriceForExtensionLine - sc.TickSize * 0.5f;
							LineUntilFutureIntersection.TransparencyLevel = TransparencyLevel;
						}
						else
							LineUntilFutureIntersection.LineValue = PriceForExtensionLine;

						LineUntilFutureIntersection.LineColor = Subgraph_ExtensionLineProperties.PrimaryColor;
						LineUntilFutureIntersection.LineWidth = Subgraph_ExtensionLineProperties.LineWidth;
						LineUntilFutureIntersection.LineStyle = Subgraph_ExtensionLineProperties.LineStyle;

						if (Input_DrawExtensionLinesUntilEndOfChart.GetYesNo())
							LineUntilFutureIntersection.AlwaysExtendToEndOfChart = true;

						sc.AddLineUntilFutureIntersectionEx(LineUntilFutureIntersection);

						LineID++;
					}
				}

				if (AvailableSubgraphIndex < SC_SUBGRAPHS_AVAILABLE - 13)
					++AvailableSubgraphIndex;

				if (EnableAlerts && Input_AlertNumber.GetAlertSoundNumber() > 0  && BarIndex == sc.ArraySize - 1)
				{

					sc.SetAlert(Input_AlertNumber.GetAlertSoundNumber() - 1 , "Volume threshold triggered");
				}
			}
		}
	}
}
