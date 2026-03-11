---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 04:33:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1773217628 27
1773217633 27
1773217638 27
1773217643 27
1773217648 27
1773217653 27
1773217658 27
1773217663 32
1773217668 32
1773217673 32
1773217678 32
1773217683 32
1773217688 32
1773217693 32
1773217698 32
1773217703 32
1773217708 32
1773217713 32
1773217718 32
1773217723 32
```
</details>

---

