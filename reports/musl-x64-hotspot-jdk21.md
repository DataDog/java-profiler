---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795001521 62
1795001526 62
1795001531 62
1795001536 62
1795001541 62
1795001546 62
1795001551 62
1795001556 62
1795001561 62
1795001566 64
1795001571 64
1795001576 62
1795001581 62
1795001586 62
1795001591 62
1795001596 62
1795001601 62
1795001606 62
1795001611 62
1795001616 62
```
</details>

---

