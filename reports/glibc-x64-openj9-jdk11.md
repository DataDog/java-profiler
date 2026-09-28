---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 08:01:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 50-61 cores)</summary>

```
1790596535 50
1790596540 50
1790596545 61
1790596550 61
1790596555 50
1790596560 50
1790596565 50
1790596570 50
1790596575 50
1790596580 50
1790596585 50
1790596590 50
1790596595 50
1790596600 50
1790596605 50
1790596610 50
1790596615 50
1790596620 50
1790596625 50
1790596630 50
```
</details>

---

