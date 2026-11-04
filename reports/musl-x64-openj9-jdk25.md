---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 10 |
| Allocations | 445 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1793830736 79
1793830741 79
1793830746 79
1793830751 79
1793830756 79
1793830761 79
1793830766 79
1793830771 79
1793830776 79
1793830781 79
1793830786 79
1793830791 79
1793830796 79
1793830801 79
1793830806 79
1793830811 77
1793830816 77
1793830821 77
1793830826 77
1793830831 79
```
</details>

---

