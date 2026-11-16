---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:18:23 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 60-68 cores)</summary>

```
1794823849 60
1794823854 60
1794823859 60
1794823864 60
1794823869 60
1794823874 60
1794823879 60
1794823884 64
1794823889 64
1794823894 64
1794823899 64
1794823904 64
1794823909 64
1794823914 66
1794823919 66
1794823924 66
1794823929 66
1794823934 66
1794823939 66
1794823944 66
```
</details>

---

