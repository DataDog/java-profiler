---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 06:12:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
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
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795172844 50
1795172849 50
1795172854 50
1795172859 50
1795172864 50
1795172869 50
1795172874 50
1795172879 50
1795172884 50
1795172889 50
1795172894 50
1795172899 50
1795172904 50
1795172909 50
1795172914 50
1795172919 50
1795172924 50
1795172929 50
1795172934 50
1795172939 50
```
</details>

---

