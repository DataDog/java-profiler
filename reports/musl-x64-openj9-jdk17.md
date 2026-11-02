---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:03:42 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 53-88 cores)</summary>

```
1793620770 53
1793620775 53
1793620780 53
1793620785 53
1793620790 53
1793620795 53
1793620800 53
1793620805 62
1793620810 62
1793620815 88
1793620820 88
1793620825 88
1793620830 88
1793620835 88
1793620840 88
1793620845 88
1793620850 88
1793620855 80
1793620860 80
1793620865 80
```
</details>

---

