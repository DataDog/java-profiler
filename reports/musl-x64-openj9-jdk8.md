---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793830716 61
1793830721 59
1793830726 59
1793830731 59
1793830736 59
1793830741 59
1793830746 59
1793830751 61
1793830756 61
1793830761 61
1793830766 61
1793830771 61
1793830776 61
1793830781 61
1793830786 61
1793830791 61
1793830796 61
1793830801 61
1793830806 61
1793830811 61
```
</details>

---

