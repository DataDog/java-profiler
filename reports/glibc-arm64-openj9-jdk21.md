---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 06:10:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 8 |
| Allocations | 176 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1786356437 30
1786356442 30
1786356447 30
1786356452 30
1786356457 30
1786356462 30
1786356467 30
1786356472 30
1786356477 30
1786356482 30
1786356487 30
1786356492 30
1786356497 30
1786356502 30
1786356507 28
1786356512 28
1786356517 28
1786356522 28
1786356527 28
1786356532 28
```
</details>

---

