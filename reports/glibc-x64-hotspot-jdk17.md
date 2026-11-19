---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 66-87 cores)</summary>

```
1795107960 66
1795107965 66
1795107970 66
1795107975 66
1795107980 87
1795107985 87
1795107990 85
1795107995 85
1795108000 85
1795108005 85
1795108010 85
1795108015 85
1795108020 85
1795108025 85
1795108030 85
1795108035 85
1795108040 85
1795108045 85
1795108050 85
1795108055 85
```
</details>

---

