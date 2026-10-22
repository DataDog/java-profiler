---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:38:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792675894 48
1792675899 48
1792675904 48
1792675909 48
1792675914 48
1792675919 43
1792675924 43
1792675929 43
1792675934 43
1792675939 43
1792675944 43
1792675949 43
1792675954 43
1792675959 43
1792675964 43
1792675969 43
1792675974 43
1792675979 43
1792675984 43
1792675989 43
```
</details>

---

