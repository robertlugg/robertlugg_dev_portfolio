declare module "gaussian-process" {
  export function create(options?: { kernel?: string; noise?: number }): {
    train: (x: number[][], y: number[]) => void;
    predict: (x: number[][]) => [number, number][];
  };
}
