---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1795793646 52
1795793651 52
1795793656 52
1795793661 52
1795793666 52
1795793671 52
1795793676 52
1795793681 52
1795793686 52
1795793691 52
1795793696 52
1795793701 57
1795793706 57
1795793711 57
1795793716 59
1795793721 59
1795793726 50
1795793731 50
1795793736 50
1795793741 50
```
</details>

---

