---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 16:14:08 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 30-61 cores)</summary>

```
1786133302 30
1786133307 61
1786133312 61
1786133317 61
1786133322 61
1786133327 61
1786133332 40
1786133337 40
1786133342 40
1786133347 40
1786133352 40
1786133357 40
1786133362 40
1786133367 40
1786133372 40
1786133377 40
1786133382 57
1786133387 57
1786133392 57
1786133397 57
```
</details>

---

