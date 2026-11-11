---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:05:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 64-92 cores)</summary>

```
1794391201 92
1794391206 92
1794391211 92
1794391216 92
1794391221 74
1794391226 74
1794391231 74
1794391236 64
1794391241 64
1794391246 64
1794391251 64
1794391256 64
1794391261 64
1794391266 64
1794391271 64
1794391276 68
1794391281 68
1794391286 68
1794391291 68
1794391296 68
```
</details>

---

