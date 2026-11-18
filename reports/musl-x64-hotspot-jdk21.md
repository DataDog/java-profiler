---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 36-49 cores)</summary>

```
1795027783 49
1795027788 49
1795027793 49
1795027798 49
1795027803 49
1795027808 49
1795027813 49
1795027818 49
1795027823 49
1795027828 49
1795027833 49
1795027838 49
1795027843 49
1795027848 49
1795027853 43
1795027858 43
1795027863 45
1795027868 45
1795027873 36
1795027878 36
```
</details>

---

