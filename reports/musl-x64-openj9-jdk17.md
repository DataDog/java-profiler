---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 69-87 cores)</summary>

```
1794999746 87
1794999751 87
1794999756 87
1794999761 87
1794999766 87
1794999771 87
1794999776 87
1794999781 87
1794999786 87
1794999791 87
1794999796 87
1794999801 87
1794999806 87
1794999811 87
1794999816 69
1794999821 69
1794999826 69
1794999831 69
1794999836 69
1794999841 69
```
</details>

---

