---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 11:55:11 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 41-64 cores)</summary>

```
1786636201 43
1786636206 43
1786636211 43
1786636216 43
1786636221 43
1786636226 43
1786636231 43
1786636236 43
1786636241 43
1786636246 43
1786636251 41
1786636256 41
1786636261 41
1786636266 41
1786636271 41
1786636276 41
1786636281 41
1786636286 41
1786636291 43
1786636296 43
```
</details>

---

