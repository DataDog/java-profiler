---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 22:10:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794625647 44
1794625652 44
1794625657 44
1794625662 44
1794625667 44
1794625672 44
1794625677 44
1794625682 44
1794625687 44
1794625692 44
1794625697 44
1794625702 44
1794625707 44
1794625712 44
1794625717 44
1794625722 44
1794625727 44
1794625732 44
1794625737 44
1794625742 44
```
</details>

---

