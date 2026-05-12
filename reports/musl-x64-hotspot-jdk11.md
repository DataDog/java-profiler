---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:53:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1116 |
| Sample Rate | 18.60/sec |
| Health Score | 1162% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 52-57 cores)</summary>

```
1778582851 52
1778582856 52
1778582861 52
1778582866 52
1778582871 52
1778582876 52
1778582881 52
1778582886 57
1778582891 57
1778582896 57
1778582901 57
1778582906 57
1778582911 57
1778582916 57
1778582921 57
1778582926 57
1778582931 57
1778582936 57
1778582941 57
1778582946 57
```
</details>

---

