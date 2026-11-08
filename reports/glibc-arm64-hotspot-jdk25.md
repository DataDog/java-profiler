---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794165884 24
1794165889 24
1794165894 24
1794165899 24
1794165904 24
1794165909 24
1794165914 29
1794165919 29
1794165924 34
1794165929 34
1794165934 34
1794165939 34
1794165944 34
1794165949 34
1794165954 34
1794165959 34
1794165964 34
1794165969 34
1794165974 34
1794165979 34
```
</details>

---

