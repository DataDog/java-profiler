---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 07:14:57 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 66-96 cores)</summary>

```
1795003781 66
1795003786 66
1795003791 70
1795003796 70
1795003801 70
1795003806 70
1795003811 70
1795003816 70
1795003821 70
1795003826 70
1795003831 70
1795003836 70
1795003841 79
1795003846 79
1795003851 79
1795003856 79
1795003861 79
1795003866 79
1795003871 79
1795003876 96
```
</details>

---

