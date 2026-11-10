---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 18:15:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (5 unique values: 50-59 cores)</summary>

```
1794352250 57
1794352255 59
1794352260 59
1794352265 58
1794352270 58
1794352275 58
1794352280 58
1794352285 58
1794352290 58
1794352295 58
1794352300 58
1794352305 50
1794352310 50
1794352315 50
1794352320 50
1794352325 50
1794352330 51
1794352335 51
1794352340 51
1794352345 51
```
</details>

---

