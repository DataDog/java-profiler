---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:32:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 25-30 cores)</summary>

```
1794497285 28
1794497290 28
1794497295 28
1794497300 28
1794497305 28
1794497310 28
1794497315 28
1794497320 28
1794497325 28
1794497330 28
1794497335 28
1794497340 26
1794497345 26
1794497350 26
1794497355 26
1794497360 26
1794497365 26
1794497370 28
1794497375 28
1794497380 28
```
</details>

---

