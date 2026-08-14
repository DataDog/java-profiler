---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 10:14:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 14 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1786716535 53
1786716540 53
1786716545 53
1786716550 53
1786716555 53
1786716560 53
1786716565 53
1786716570 53
1786716575 53
1786716580 53
1786716585 53
1786716590 53
1786716595 53
1786716600 53
1786716605 53
1786716610 53
1786716615 53
1786716620 53
1786716625 53
1786716630 53
```
</details>

---

