---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 09:53:39 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 66-78 cores)</summary>

```
1795618173 78
1795618178 78
1795618183 78
1795618188 78
1795618193 66
1795618198 66
1795618203 66
1795618208 66
1795618213 66
1795618218 66
1795618223 66
1795618228 66
1795618233 66
1795618238 66
1795618243 66
1795618248 66
1795618253 73
1795618258 73
1795618263 73
1795618268 73
```
</details>

---

