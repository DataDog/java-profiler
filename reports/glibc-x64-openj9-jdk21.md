---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:22:26 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1795198637 28
1795198642 28
1795198647 28
1795198652 28
1795198657 28
1795198662 28
1795198667 28
1795198672 28
1795198677 28
1795198682 28
1795198687 28
1795198692 28
1795198697 28
1795198702 28
1795198707 30
1795198712 30
1795198717 30
1795198722 30
1795198727 30
1795198732 30
```
</details>

---

