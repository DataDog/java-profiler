---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-06 06:33:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1092 |
| Sample Rate | 18.20/sec |
| Health Score | 1137% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 17-32 cores)</summary>

```
1770377298 32
1770377303 32
1770377308 32
1770377313 32
1770377318 32
1770377323 32
1770377328 32
1770377333 32
1770377338 32
1770377343 32
1770377348 17
1770377353 17
1770377358 17
1770377363 17
1770377368 17
1770377373 17
1770377378 17
1770377383 17
1770377388 17
1770377393 17
```
</details>

---

