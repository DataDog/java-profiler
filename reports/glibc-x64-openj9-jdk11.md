---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:47:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 56-75 cores)</summary>

```
1789731711 71
1789731716 71
1789731721 71
1789731726 73
1789731731 73
1789731736 73
1789731741 73
1789731746 73
1789731751 73
1789731756 73
1789731761 75
1789731766 75
1789731771 75
1789731776 75
1789731781 75
1789731786 75
1789731791 75
1789731796 75
1789731801 75
1789731806 75
```
</details>

---

