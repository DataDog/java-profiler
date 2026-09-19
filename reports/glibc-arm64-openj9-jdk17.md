---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-19 00:58:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789793665 31
1789793670 31
1789793675 31
1789793680 31
1789793685 31
1789793690 31
1789793695 31
1789793700 31
1789793705 31
1789793710 26
1789793715 26
1789793720 26
1789793725 26
1789793730 26
1789793735 26
1789793740 26
1789793745 26
1789793750 26
1789793755 26
1789793760 31
```
</details>

---

