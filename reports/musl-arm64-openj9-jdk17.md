---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 08:24:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1790684444 46
1790684449 46
1790684454 46
1790684459 46
1790684464 46
1790684469 46
1790684474 45
1790684479 45
1790684484 45
1790684489 45
1790684494 45
1790684499 45
1790684504 45
1790684509 45
1790684514 45
1790684519 45
1790684524 46
1790684529 46
1790684534 46
1790684539 46
```
</details>

---

