---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 05:49:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 40-81 cores)</summary>

```
1786441474 40
1786441479 40
1786441484 40
1786441489 40
1786441494 40
1786441499 40
1786441504 40
1786441509 40
1786441514 40
1786441519 40
1786441524 40
1786441529 40
1786441534 60
1786441539 60
1786441544 81
1786441549 81
1786441554 81
1786441559 81
1786441564 76
1786441569 76
```
</details>

---

