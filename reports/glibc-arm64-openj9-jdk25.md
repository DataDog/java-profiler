---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 08:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790684459 32
1790684464 32
1790684469 32
1790684474 32
1790684479 32
1790684484 32
1790684489 32
1790684494 32
1790684499 32
1790684504 32
1790684509 32
1790684514 32
1790684519 32
1790684524 32
1790684529 32
1790684534 32
1790684539 32
1790684544 32
1790684549 32
1790684554 32
```
</details>

---

