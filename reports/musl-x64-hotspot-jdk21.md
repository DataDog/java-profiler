---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 18:13:26 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1777414055 64
1777414060 64
1777414065 64
1777414070 64
1777414075 64
1777414080 64
1777414085 50
1777414090 50
1777414095 50
1777414100 50
1777414105 50
1777414110 50
1777414115 50
1777414120 50
1777414125 50
1777414130 50
1777414135 50
1777414140 50
1777414145 50
1777414150 50
```
</details>

---

