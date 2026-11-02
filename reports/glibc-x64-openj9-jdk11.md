---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:41:17 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1793633756 70
1793633761 70
1793633766 70
1793633771 70
1793633776 70
1793633781 70
1793633786 70
1793633791 70
1793633796 70
1793633801 70
1793633806 70
1793633811 70
1793633816 70
1793633821 70
1793633826 70
1793633831 70
1793633836 72
1793633841 72
1793633846 72
1793633851 72
```
</details>

---

