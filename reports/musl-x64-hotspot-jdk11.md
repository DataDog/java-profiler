---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:00:12 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 8 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1794581686 32
1794581691 32
1794581696 32
1794581701 23
1794581706 23
1794581711 23
1794581716 23
1794581721 23
1794581726 23
1794581731 23
1794581736 23
1794581741 23
1794581746 23
1794581751 23
1794581756 23
1794581761 23
1794581766 23
1794581771 23
1794581776 23
1794581781 23
```
</details>

---

