---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:12:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795172848 50
1795172853 50
1795172858 50
1795172863 50
1795172868 50
1795172873 50
1795172878 50
1795172883 50
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
1795172944 50
```
</details>

---

