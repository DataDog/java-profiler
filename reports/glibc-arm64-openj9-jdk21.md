---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 05:49:16 EDT

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
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1786441464 30
1786441469 30
1786441474 30
1786441479 30
1786441484 30
1786441489 30
1786441494 30
1786441499 30
1786441504 30
1786441509 27
1786441514 27
1786441519 27
1786441524 27
1786441529 27
1786441534 27
1786441539 27
1786441544 27
1786441549 27
1786441554 27
1786441559 27
```
</details>

---

