---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 07:07:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791543736 48
1791543741 48
1791543746 48
1791543751 48
1791543756 48
1791543761 48
1791543766 48
1791543771 48
1791543776 48
1791543781 48
1791543786 43
1791543791 43
1791543796 43
1791543801 43
1791543806 43
1791543811 43
1791543816 43
1791543821 43
1791543826 43
1791543831 43
```
</details>

---

