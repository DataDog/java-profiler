---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-24 17:04:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 70-83 cores)</summary>

```
1777064256 74
1777064261 74
1777064266 74
1777064271 74
1777064276 74
1777064281 70
1777064286 70
1777064291 70
1777064296 70
1777064301 70
1777064306 70
1777064311 70
1777064316 70
1777064321 70
1777064326 70
1777064331 74
1777064336 74
1777064341 74
1777064346 74
1777064351 74
```
</details>

---

