---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 06:33:10 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 50-56 cores)</summary>

```
1770377350 56
1770377355 56
1770377360 56
1770377365 56
1770377370 56
1770377375 56
1770377380 56
1770377385 54
1770377390 54
1770377395 54
1770377400 54
1770377405 54
1770377410 54
1770377415 54
1770377420 54
1770377425 54
1770377430 54
1770377435 50
1770377440 50
1770377445 50
```
</details>

---

