---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 01:01:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786683480 64
1786683485 64
1786683490 64
1786683495 64
1786683500 64
1786683505 64
1786683510 64
1786683515 64
1786683520 64
1786683525 64
1786683530 64
1786683535 64
1786683540 64
1786683545 64
1786683550 64
1786683555 64
1786683560 64
1786683565 64
1786683570 64
1786683575 64
```
</details>

---

