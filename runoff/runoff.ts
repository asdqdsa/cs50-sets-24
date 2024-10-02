const MAX_VOTERS: number = 100;
const MAX_CANDIDATES: number = 9;

const preferences: number[][] = Array.from({ length: MAX_VOTERS }, () =>
  Array(MAX_CANDIDATES).fill(0)
);
