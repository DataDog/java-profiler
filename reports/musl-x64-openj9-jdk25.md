---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:39:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 30-62 cores)</summary>

```
1795451620 30
1795451625 30
1795451630 30
1795451635 30
1795451640 30
1795451645 30
1795451650 30
1795451655 30
1795451660 30
1795451665 30
1795451670 30
1795451675 30
1795451680 30
1795451685 38
1795451690 38
1795451695 38
1795451700 38
1795451705 43
1795451710 43
1795451716 62
```
</details>

---

