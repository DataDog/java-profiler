---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 05:57:47 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 9 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794221558 48
1794221563 48
1794221568 48
1794221574 48
1794221579 48
1794221584 48
1794221589 43
1794221594 43
1794221599 43
1794221604 43
1794221609 43
1794221614 43
1794221619 43
1794221624 43
1794221629 43
1794221634 43
1794221639 43
1794221644 43
1794221649 43
1794221654 43
```
</details>

---

