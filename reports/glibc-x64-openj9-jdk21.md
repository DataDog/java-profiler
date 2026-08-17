---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:54:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786974666 30
1786974671 30
1786974676 30
1786974681 30
1786974686 30
1786974691 32
1786974696 32
1786974701 32
1786974706 32
1786974711 32
1786974716 32
1786974721 32
1786974726 32
1786974731 32
1786974736 32
1786974741 32
1786974746 32
1786974751 32
1786974756 32
1786974761 32
```
</details>

---

