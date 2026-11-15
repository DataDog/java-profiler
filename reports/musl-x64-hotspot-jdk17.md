---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 21:04:22 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 41-63 cores)</summary>

```
1794708069 63
1794708074 63
1794708079 63
1794708084 63
1794708089 43
1794708094 43
1794708099 43
1794708104 43
1794708109 43
1794708114 43
1794708119 41
1794708124 41
1794708129 41
1794708134 41
1794708139 41
1794708144 41
1794708149 41
1794708154 41
1794708159 41
1794708164 41
```
</details>

---

