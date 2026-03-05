---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-05 13:28:45 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1772734941 28
1772734946 28
1772734951 28
1772734956 28
1772734961 28
1772734966 28
1772734971 28
1772734976 28
1772734981 28
1772734986 28
1772734991 28
1772734996 28
1772735001 28
1772735006 28
1772735011 28
1772735016 28
1772735021 28
1772735026 24
1772735031 24
1772735036 24
```
</details>

---

