---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:43:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794998163 36
1794998168 36
1794998173 36
1794998178 36
1794998183 36
1794998188 36
1794998193 36
1794998198 36
1794998203 36
1794998208 36
1794998213 36
1794998218 36
1794998223 36
1794998228 36
1794998233 36
1794998238 31
1794998243 31
1794998248 31
1794998253 31
1794998258 31
```
</details>

---

