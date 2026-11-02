---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 10:41:17 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 46-49 cores)</summary>

```
1793633746 46
1793633751 46
1793633756 46
1793633761 46
1793633766 46
1793633771 46
1793633776 46
1793633781 46
1793633786 46
1793633791 46
1793633796 46
1793633801 46
1793633806 46
1793633811 46
1793633816 49
1793633821 49
1793633826 49
1793633831 49
1793633836 49
1793633841 49
```
</details>

---

