---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-17 01:04:37 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1792213184 17
1792213189 17
1792213194 17
1792213199 17
1792213204 17
1792213209 15
1792213214 15
1792213219 15
1792213224 15
1792213229 17
1792213234 17
1792213239 17
1792213244 17
1792213249 17
1792213254 17
1792213259 17
1792213264 17
1792213269 17
1792213274 17
1792213279 17
```
</details>

---

