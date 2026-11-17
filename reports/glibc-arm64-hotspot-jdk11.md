---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:33:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 26-46 cores)</summary>

```
1794932954 33
1794932959 33
1794932964 33
1794932969 33
1794932974 33
1794932979 46
1794932984 46
1794932989 46
1794932994 46
1794932999 46
1794933004 46
1794933009 46
1794933014 46
1794933019 26
1794933024 26
1794933029 26
1794933034 26
1794933039 26
1794933044 26
1794933049 26
```
</details>

---

