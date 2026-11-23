---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:58:20 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 67-70 cores)</summary>

```
1795452815 67
1795452820 67
1795452825 67
1795452830 67
1795452835 67
1795452840 67
1795452845 67
1795452850 67
1795452855 67
1795452860 67
1795452865 67
1795452870 70
1795452875 70
1795452880 70
1795452885 70
1795452890 70
1795452895 70
1795452900 70
1795452905 70
1795452910 70
```
</details>

---

