---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:10:04 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1114 |
| Sample Rate | 18.57/sec |
| Health Score | 1161% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 27-69 cores)</summary>

```
1777392245 27
1777392250 27
1777392255 27
1777392260 32
1777392265 32
1777392270 65
1777392275 65
1777392280 65
1777392285 65
1777392290 65
1777392295 65
1777392300 65
1777392305 65
1777392310 65
1777392315 65
1777392320 65
1777392325 65
1777392330 65
1777392335 65
1777392340 65
```
</details>

---

