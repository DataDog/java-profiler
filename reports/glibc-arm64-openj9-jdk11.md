---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 05:58:27 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 17-20 cores)</summary>

```
1793962444 20
1793962449 20
1793962454 20
1793962459 20
1793962464 20
1793962469 20
1793962475 20
1793962480 20
1793962485 20
1793962490 20
1793962495 20
1793962500 19
1793962505 19
1793962510 19
1793962515 19
1793962520 20
1793962525 20
1793962530 17
1793962535 17
1793962540 17
```
</details>

---

