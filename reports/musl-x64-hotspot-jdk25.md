---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-30 06:15:42 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1137 |
| Sample Rate | 18.95/sec |
| Health Score | 1184% |
| Threads | 13 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769771408 32
1769771413 32
1769771418 32
1769771423 32
1769771428 30
1769771433 30
1769771438 30
1769771443 30
1769771448 32
1769771453 32
1769771458 32
1769771463 32
1769771468 32
1769771473 32
1769771478 32
1769771483 32
1769771488 32
1769771493 32
1769771498 32
1769771503 32
```
</details>

---

