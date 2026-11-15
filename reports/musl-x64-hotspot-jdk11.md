---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:02:47 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1052 |
| Sample Rate | 17.53/sec |
| Health Score | 1096% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1794783527 64
1794783533 64
1794783538 64
1794783543 66
1794783548 66
1794783553 66
1794783558 66
1794783563 66
1794783568 66
1794783573 66
1794783578 66
1794783583 66
1794783588 66
1794783593 64
1794783598 64
1794783603 64
1794783608 64
1794783613 64
1794783618 64
1794783623 64
```
</details>

---

