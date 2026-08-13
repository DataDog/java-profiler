---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 15:42:55 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 50-59 cores)</summary>

```
1786649878 59
1786649883 59
1786649888 59
1786649893 59
1786649898 50
1786649903 50
1786649908 50
1786649913 50
1786649919 54
1786649924 54
1786649929 54
1786649934 54
1786649939 54
1786649944 54
1786649949 54
1786649954 54
1786649959 54
1786649964 54
1786649969 54
1786649974 54
```
</details>

---

