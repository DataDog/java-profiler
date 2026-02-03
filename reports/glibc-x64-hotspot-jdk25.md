---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 10:07:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 11 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1118 |
| Sample Rate | 18.63/sec |
| Health Score | 1164% |
| Threads | 13 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 52-60 cores)</summary>

```
1770130793 52
1770130798 52
1770130803 52
1770130808 52
1770130813 52
1770130818 52
1770130823 52
1770130828 52
1770130833 56
1770130838 56
1770130843 56
1770130848 56
1770130853 56
1770130858 56
1770130863 56
1770130868 56
1770130873 56
1770130878 56
1770130883 56
1770130888 56
```
</details>

---

