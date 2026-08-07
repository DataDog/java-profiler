---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 17:19:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1786137221 11
1786137226 11
1786137231 11
1786137236 11
1786137241 11
1786137246 11
1786137251 11
1786137256 11
1786137261 11
1786137266 11
1786137271 11
1786137276 11
1786137281 11
1786137286 11
1786137291 9
1786137296 9
1786137301 9
1786137306 9
1786137311 9
1786137316 9
```
</details>

---

