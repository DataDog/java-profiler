---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:54:53 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1786974661 92
1786974666 92
1786974671 92
1786974676 94
1786974681 94
1786974686 94
1786974691 94
1786974696 96
1786974701 96
1786974706 96
1786974711 96
1786974716 96
1786974721 96
1786974726 96
1786974731 96
1786974736 96
1786974741 96
1786974746 96
1786974751 96
1786974756 96
```
</details>

---

