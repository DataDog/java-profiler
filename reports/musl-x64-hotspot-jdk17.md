---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:39:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 78-81 cores)</summary>

```
1795196076 81
1795196081 81
1795196086 81
1795196091 81
1795196097 81
1795196102 81
1795196107 81
1795196112 81
1795196117 81
1795196122 81
1795196127 81
1795196132 81
1795196137 78
1795196142 78
1795196147 78
1795196152 78
1795196157 78
1795196162 78
1795196167 78
1795196172 78
```
</details>

---

