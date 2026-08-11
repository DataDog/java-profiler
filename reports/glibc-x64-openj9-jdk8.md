---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-11 05:49:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1786441469 46
1786441474 46
1786441479 46
1786441484 46
1786441489 46
1786441494 46
1786441499 46
1786441504 46
1786441509 46
1786441514 46
1786441519 46
1786441524 46
1786441529 41
1786441534 41
1786441539 41
1786441544 41
1786441549 41
1786441554 41
1786441559 41
1786441564 41
```
</details>

---

