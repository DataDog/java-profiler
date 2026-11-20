---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 06:12:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795172854 45
1795172859 45
1795172864 45
1795172869 45
1795172874 45
1795172879 45
1795172884 45
1795172889 45
1795172894 45
1795172899 45
1795172904 50
1795172909 50
1795172914 50
1795172919 50
1795172924 50
1795172929 50
1795172934 50
1795172939 50
1795172944 50
1795172949 50
```
</details>

---

