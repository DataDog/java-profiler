---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:54:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794584947 48
1794584952 48
1794584957 48
1794584962 48
1794584967 48
1794584972 48
1794584977 48
1794584982 48
1794584987 48
1794584993 36
1794584998 36
1794585003 36
1794585008 36
1794585013 36
1794585018 36
1794585023 36
1794585028 36
1794585033 36
1794585038 36
1794585043 36
```
</details>

---

