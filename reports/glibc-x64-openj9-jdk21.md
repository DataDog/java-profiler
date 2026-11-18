---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1794999759 74
1794999764 74
1794999769 74
1794999774 74
1794999779 76
1794999784 76
1794999789 76
1794999794 76
1794999799 76
1794999804 76
1794999809 76
1794999814 76
1794999819 76
1794999824 76
1794999829 76
1794999834 76
1794999839 76
1794999844 76
1794999849 76
1794999854 76
```
</details>

---

