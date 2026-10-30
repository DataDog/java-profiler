---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:23:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1793373484 46
1793373489 46
1793373494 46
1793373499 46
1793373504 41
1793373509 41
1793373514 41
1793373519 41
1793373524 43
1793373529 43
1793373534 43
1793373539 43
1793373544 43
1793373549 43
1793373554 43
1793373559 43
1793373564 43
1793373569 43
1793373574 43
1793373579 43
```
</details>

---

