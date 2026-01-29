---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769702859 24
1769702864 24
1769702869 24
1769702874 24
1769702879 24
1769702884 24
1769702889 24
1769702894 24
1769702899 24
1769702904 24
1769702909 24
1769702914 24
1769702919 24
1769702924 24
1769702929 24
1769702934 24
1769702939 24
1769702944 24
1769702949 24
1769702954 24
```
</details>

---

