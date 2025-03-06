// src/hooks/useBayesianSimulation.ts
import { useState, useEffect, useRef } from "react";
import { gpRegression, trueFunction, pickUCB, pickEI, pickPI } from "../utils/gpUtils";
import type { PlotData } from "plotly.js";

const X_PRED = Array.from({ length: 100 }, (_, i) => (i / 100) * 4 * Math.PI);

export const useBayesianSimulation = (acquisitionFn: string, initialSteps: number = 20) => {
  const [bayesianData, setBayesianData] = useState<PlotData[]>([]);
  const [rmsErrors, setRmsErrors] = useState<number[]>([]);
  const [logs, setLogs] = useState<string[]>([]);
  const [totalSteps, setTotalSteps] = useState(initialSteps);

  // Refs for continuity
  const sampledXRef = useRef<number[]>([]);
  const sampledYRef = useRef<number[]>([]);

  useEffect(() => {
    // Only run if we still have steps to compute
    if (sampledXRef.current.length >= totalSteps) {
      return;
    }

    const runSimulation = async () => {
      for (let step = sampledXRef.current.length; step < totalSteps; step++) {
        if (step === 0) {
            // Step 0: initial state, no sample is added.
            setLogs((prev) => [...prev, "Step 0: initial state, no sample added.\n"]);
            continue;
          }
          let nextX: number;
          let nextY: number;
          let rmsError = 0;
                    if (step === 1) {
            // For the first sample, pick the center of the X domain.
            nextX = X_PRED[Math.floor(X_PRED.length / 2)];
            nextY = trueFunction(nextX);
            rmsError = 0; // or calculate a baseline if desired
          } else {
            // For steps >= 2, perform GP regression on the accumulated samples.
            const { mean, stdDev } = gpRegression(sampledXRef.current, sampledYRef.current, X_PRED);
                      // Decide next sample based on chosen acquisitionFn.
            switch (acquisitionFn) {
              case "EI":
                nextX = pickEI(X_PRED, mean, stdDev, sampledYRef.current);
                break;
              case "PI":
                nextX = pickPI(X_PRED, mean, stdDev, sampledYRef.current);
                break;
              case "UCB":
              default:
                nextX = pickUCB(X_PRED, mean, stdDev, 2.0);
                break;
            }
            nextY = trueFunction(nextX);
            rmsError = Math.sqrt(
              mean.reduce((sum, m, i) => sum + (m - trueFunction(X_PRED[i])) ** 2, 0) / mean.length
            );
          }
                     // Append new sample (for step 1 and beyond)
         sampledXRef.current.push(nextX);
         sampledYRef.current.push(nextY);
                  // Update plot data with the cumulative samples.
         setBayesianData((prev) => [
           ...prev,
           {
             x: [...sampledXRef.current],
             y: [...sampledYRef.current],
             type: "scatter",
             mode: "lines+markers",
             marker: { size: 8 },
           } as PlotData,
         ]);
                  setRmsErrors((prev) => [...prev, rmsError]);
                  setLogs((prev) => [
           ...prev,
           `Step ${step}: sample x=${nextX.toFixed(2)}, y=${nextY.toFixed(2)}, using ${acquisitionFn}\n`,
         ]);
        }
      setLogs((prev) => [...prev, "Simulation completed.\n"]);
    };

    runSimulation();
  }, [totalSteps, acquisitionFn]);

  return { bayesianData, rmsErrors, totalSteps, setTotalSteps, logs };
};
