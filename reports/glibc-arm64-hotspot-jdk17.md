---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1795793694 40
1795793699 40
1795793704 40
1795793709 40
1795793714 40
1795793719 40
1795793724 40
1795793729 40
1795793734 40
1795793739 40
1795793744 40
1795793749 40
1795793754 40
1795793759 40
1795793764 40
1795793769 40
1795793774 40
1795793779 40
1795793784 40
1795793789 40
```
</details>

---

