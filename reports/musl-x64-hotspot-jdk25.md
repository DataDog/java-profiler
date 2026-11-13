---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 17:21:30 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 83-91 cores)</summary>

```
1794608201 83
1794608206 83
1794608211 83
1794608216 83
1794608221 83
1794608226 91
1794608231 91
1794608236 91
1794608241 91
1794608246 91
1794608251 91
1794608256 89
1794608261 89
1794608266 89
1794608271 89
1794608276 89
1794608281 89
1794608286 89
1794608291 91
1794608296 91
```
</details>

---

