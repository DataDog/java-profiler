---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 83-92 cores)</summary>

```
1795434641 83
1795434646 83
1795434651 83
1795434656 92
1795434661 92
1795434666 92
1795434671 92
1795434676 83
1795434681 83
1795434686 83
1795434691 83
1795434696 83
1795434701 83
1795434706 83
1795434711 83
1795434716 83
1795434721 83
1795434726 83
1795434731 83
1795434736 85
```
</details>

---

