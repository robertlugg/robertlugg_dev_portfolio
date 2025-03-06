import { inv, multiply, transpose, subtract } from "mathjs";

// Radial Basis Function (RBF) kernel
export function rbfKernel(x1: number, x2: number, lengthScale = 1.0): number {
  return Math.exp(-((x1 - x2) ** 2) / (2 * lengthScale ** 2));
}

// Compute a full NxN kernel matrix for inputs X
export function computeKernelMatrix(
  X: number[],
  lengthScale = 1.0,
): number[][] {
  return X.map((x1) => X.map((x2) => rbfKernel(x1, x2, lengthScale)));
}

// Perform Gaussian Process regression
// Returns an object with the predicted mean and standard deviation for each x in Xtest.
export function gpRegression(
  Xtrain: number[],
  Ytrain: number[],
  Xtest: number[],
  lengthScale = 1.0,
  noise = 1e-6,
) {
  const K = computeKernelMatrix(Xtrain, lengthScale);
  // Add noise on the diagonal for numerical stability
  for (let i = 0; i < K.length; i++) {
    K[i][i] += noise;
  }
  const invK = inv(K);
  const Ks = Xtrain.map((xt) =>
    Xtest.map((x) => rbfKernel(xt, x, lengthScale)),
  );
  const Kss = computeKernelMatrix(Xtest, lengthScale);

  // Compute the mean prediction: mean = transpose(Ks) * invK * Ytrain
  const mean = multiply(transpose(Ks), multiply(invK, Ytrain)) as number[];

  // Compute the posterior covariance: cov = Kss - transpose(Ks) * invK * Ks
  const covPart = multiply(transpose(Ks), multiply(invK, Ks)) as number[][];
  const cov = subtract(Kss, covPart) as number[][];
  // Extract standard deviation from the diagonal of the covariance matrix
  const stdDev = cov.map((row, i) => Math.sqrt(Math.max(row[i], 1e-10)));

  return { mean, stdDev };
}

// The "true" function we want to model, e.g., sin(x)
export function trueFunction(x: number): number {
  return Math.sin(x);
}

/* -------------------
   Acquisition Functions
   ------------------- */

// UCB: Upper Confidence Bound (default exploration parameter beta=2.0)
export function pickUCB(
  X_pred: number[],
  mean: number[],
  stdDev: number[],
  beta = 2.0,
): number {
  let bestVal = -Infinity;
  let bestX = X_pred[0];
  for (let i = 0; i < X_pred.length; i++) {
    const val = mean[i] + beta * stdDev[i];
    if (val > bestVal) {
      bestVal = val;
      bestX = X_pred[i];
    }
  }
  return bestX;
}

// Expected Improvement (EI)
// Uses a simple normal distribution approximation.
export function pickEI(
  X_pred: number[],
  mean: number[],
  stdDev: number[],
  samplesY: number[],
): number {
  const fBest = Math.max(...samplesY);
  let bestEI = -Infinity;
  let bestX = X_pred[0];
  for (let i = 0; i < X_pred.length; i++) {
    const improvement = mean[i] - fBest;
    let ei = 0;
    if (stdDev[i] > 1e-9) {
      const z = improvement / stdDev[i];
      ei = improvement * cdf(z) + stdDev[i] * pdf(z);
    } else {
      ei = improvement > 0 ? improvement : 0;
    }
    if (ei > bestEI) {
      bestEI = ei;
      bestX = X_pred[i];
    }
  }
  return bestX;
}

// Probability of Improvement (PI)
export function pickPI(
  X_pred: number[],
  mean: number[],
  stdDev: number[],
  samplesY: number[],
): number {
  const fBest = Math.max(...samplesY);
  let bestPI = -Infinity;
  let bestX = X_pred[0];
  for (let i = 0; i < X_pred.length; i++) {
    let pi = 0;
    if (stdDev[i] > 1e-9) {
      const z = (mean[i] - fBest) / stdDev[i];
      pi = cdf(z);
    } else {
      pi = mean[i] > fBest ? 1 : 0;
    }
    if (pi > bestPI) {
      bestPI = pi;
      bestX = X_pred[i];
    }
  }
  return bestX;
}

/* -------------------
   Helper functions for EI and PI
   ------------------- */

// Normal probability density function (PDF) for standard normal
function pdf(z: number): number {
  return Math.exp(-0.5 * z * z) / Math.sqrt(2 * Math.PI);
}

// Cumulative distribution function (CDF) for standard normal
function cdf(z: number): number {
  // Abramowitz and Stegun approximation for the error function
  const t = 1 / (1 + 0.2316419 * Math.abs(z));
  const d = 0.3989423 * Math.exp((-z * z) / 2);
  let prob =
    d *
    t *
    (0.3193815 +
      t * (-0.3565638 + t * (1.781478 + t * (-1.821256 + t * 1.330274))));
  if (z > 0) {
    prob = 1 - prob;
  }
  return prob;
}
