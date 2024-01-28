# SierraChart-Studies

## Volume At Price Threshold Alert V2 Extended
Same study as the native one from SierraChart, but with complementary filters:

1) Filter by Bar type : Bulish, Bearish or Both
2) Filter by position (Above/Bellow) to Reference Price (OHLC) +- offset (in ticks).

### Configuration
* Enable Extended Configuration Yes/No : select yes to use.
* Bearish/Bullish Bar : Alert on Bearish or Bulish or Both Candles
* Price of alert Above/Bellow Base price (OHLC) + Offset
  * OHLC Base price : None (no price alerte comparaison)
  * Price offset Bellow/Above : in tick
  * Above/Bellow Price + Offset

### use case
#### mzpack absorption
Use twice, one for support and one for resistance
* support = sell imbalances bellow bar close - depth ticks
* resistance = buy imbalance above bar close + depth ticks

<table>
  <tr>
    <th>mzpack config</th>
    <th>SierraChart support</th>
    <th>SierraChart resistance</th>
  </tr>
  <tr>
    <td>Absorption %</td>
    <td>Comparison Method = Ask Volume Bid Volume Diagonal Ratio<br>
        Percentage Threshold = - Absorption % - 100%</td>
    <td>Comparison Method = Ask Volume Bid Volume Diagonal Ratio<br>
        Percentage Threshold = Absorption % + 100%</td>
  </tr>
  <tr>
    <td></td>
    <td>Bearish/Bullish Bar = Both</td>
    <td>Bearish/Bullish Bar = Both</td>
  </tr>
  <tr>
    <td></td>
    <td>Enable Zero Bid/Ask Compares = Yes<br>
        Zero Value Compare Action = Set Percentage to +/- 1000%</td>
    <td>Enable Zero Bid/Ask Compares = Yes<br>
        Zero Value Compare Action = Set Percentage to +/- 1000%</td>
  </tr>
  <tr>
    <td>Depth</td>
    <td>Price offset Bellow/Above = - Depth</td>
    <td>Price offset Bellow/Above = Depth</td>
  </tr>
  <tr>
    <td>S/R zones: enable</td>
    <td>Draw Extension Lines = All Prices in Adjacent Alerts<br>
        Draw Extension Lines With Transparent Range = Yes</td>
    <td>Draw Extension Lines = All Prices in Adjacent Alerts<br>
        Draw Extension Lines With Transparent Range = Yes</td>
  </tr>
  <tr>
    <td>S/R zones: consecutive levels</td>
    <td>Highlight Adjacent Alerts Minimum Group Size = S/R zones: consecutive levels</td>
    <td>Highlight Adjacent Alerts Minimum Group Size = S/R zones: consecutive levels</td>
  </tr>
</table>
