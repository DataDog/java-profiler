---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 05:57:48 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 50-56 cores)</summary>

```
1794221570 50
1794221575 50
1794221580 54
1794221585 54
1794221590 54
1794221595 54
1794221600 54
1794221605 54
1794221610 54
1794221615 54
1794221620 54
1794221625 54
1794221630 54
1794221635 54
1794221640 54
1794221645 54
1794221650 54
1794221655 54
1794221660 54
1794221665 54
```
</details>

---

