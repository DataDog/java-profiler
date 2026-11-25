---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:39:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 61-64 cores)</summary>

```
1795606591 64
1795606596 64
1795606601 64
1795606607 64
1795606612 64
1795606617 64
1795606622 64
1795606627 64
1795606632 64
1795606637 64
1795606642 64
1795606647 64
1795606652 64
1795606657 64
1795606662 64
1795606667 64
1795606672 64
1795606677 64
1795606682 64
1795606687 64
```
</details>

---

