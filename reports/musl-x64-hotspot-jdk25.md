---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:26:04 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 71-80 cores)</summary>

```
1794489676 73
1794489681 73
1794489686 73
1794489691 73
1794489696 73
1794489701 73
1794489706 73
1794489711 73
1794489716 73
1794489721 73
1794489726 73
1794489731 71
1794489736 71
1794489741 71
1794489746 71
1794489751 71
1794489756 71
1794489761 71
1794489766 71
1794489771 71
```
</details>

---

