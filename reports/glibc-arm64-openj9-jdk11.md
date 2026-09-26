---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-26 01:03:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 10 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1790398401 15
1790398406 17
1790398411 17
1790398416 17
1790398421 17
1790398426 17
1790398431 17
1790398437 17
1790398442 17
1790398447 17
1790398452 17
1790398457 17
1790398462 17
1790398467 17
1790398472 17
1790398477 17
1790398482 17
1790398487 17
1790398492 17
1790398497 17
```
</details>

---

