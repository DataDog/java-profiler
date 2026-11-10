---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:14:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 18-31 cores)</summary>

```
1794352270 18
1794352275 18
1794352280 18
1794352285 18
1794352290 18
1794352295 18
1794352300 18
1794352305 18
1794352310 18
1794352315 18
1794352320 31
1794352325 31
1794352330 31
1794352335 31
1794352340 31
1794352345 31
1794352350 31
1794352355 31
1794352360 31
1794352365 31
```
</details>

---

