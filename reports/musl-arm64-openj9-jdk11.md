---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 11 |
| Allocations | 199 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1790074851 23
1790074856 23
1790074861 23
1790074866 23
1790074871 23
1790074876 23
1790074881 23
1790074886 23
1790074891 23
1790074896 23
1790074901 23
1790074906 23
1790074911 23
1790074916 23
1790074921 23
1790074926 28
1790074931 28
1790074936 28
1790074941 28
1790074946 28
```
</details>

---

