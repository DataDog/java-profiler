---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 06:12:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 40-50 cores)</summary>

```
1795172859 45
1795172864 45
1795172869 45
1795172874 45
1795172879 45
1795172884 45
1795172889 45
1795172894 45
1795172899 45
1795172904 45
1795172909 45
1795172914 45
1795172919 50
1795172924 50
1795172929 50
1795172934 50
1795172939 50
1795172944 50
1795172949 50
1795172954 45
```
</details>

---

