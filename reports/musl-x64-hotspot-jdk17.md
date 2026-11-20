---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:39:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (6 unique values: 80-96 cores)</summary>

```
1795170699 80
1795170704 80
1795170709 80
1795170714 80
1795170719 82
1795170724 82
1795170729 82
1795170734 84
1795170739 84
1795170744 84
1795170749 84
1795170754 84
1795170759 94
1795170764 94
1795170769 94
1795170774 94
1795170779 96
1795170784 96
1795170789 96
1795170794 96
```
</details>

---

