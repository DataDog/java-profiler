---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 08:29:04 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 80-96 cores)</summary>

```
1786710262 80
1786710267 80
1786710272 80
1786710277 80
1786710282 80
1786710287 88
1786710292 88
1786710297 88
1786710302 88
1786710307 88
1786710312 88
1786710317 88
1786710322 88
1786710327 88
1786710332 96
1786710337 96
1786710342 96
1786710347 96
1786710352 96
1786710357 96
```
</details>

---

