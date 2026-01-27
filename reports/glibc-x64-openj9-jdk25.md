---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 25.77/sec |
| Health Score | 1611% |
| Threads | 12 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 32.80/sec |
| Health Score | 2050% |
| Threads | 13 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 79-88 cores)</summary>

```
1769526892 84
1769526897 88
1769526902 88
1769526907 88
1769526912 88
1769526917 88
1769526922 88
1769526927 88
1769526932 88
1769526937 88
1769526942 88
1769526947 88
1769526952 79
1769526957 79
1769526962 79
1769526967 79
1769526972 79
1769526977 79
1769526982 79
1769526987 79
```
</details>

---

