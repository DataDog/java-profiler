---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:30:27 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 12 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 81-92 cores)</summary>

```
1794997526 81
1794997531 81
1794997536 81
1794997541 83
1794997546 83
1794997551 81
1794997556 81
1794997561 83
1794997566 83
1794997571 83
1794997576 81
1794997581 81
1794997586 81
1794997591 83
1794997596 83
1794997601 92
1794997606 92
1794997611 92
1794997616 86
1794997621 86
```
</details>

---

