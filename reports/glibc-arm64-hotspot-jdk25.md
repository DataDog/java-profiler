---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:23:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 11 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 15-29 cores)</summary>

```
1795108725 29
1795108730 29
1795108735 29
1795108740 17
1795108745 17
1795108750 17
1795108755 17
1795108760 17
1795108765 17
1795108770 17
1795108775 17
1795108780 17
1795108785 17
1795108790 17
1795108795 17
1795108800 17
1795108805 17
1795108810 17
1795108815 17
1795108820 17
```
</details>

---

