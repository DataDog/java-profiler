---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:14:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (3 unique values: 17-37 cores)</summary>

```
1794352225 20
1794352230 20
1794352235 20
1794352240 20
1794352245 20
1794352250 20
1794352255 20
1794352260 20
1794352265 20
1794352270 20
1794352275 20
1794352280 20
1794352285 20
1794352290 20
1794352295 20
1794352300 20
1794352305 37
1794352310 37
1794352315 37
1794352320 37
```
</details>

---

