---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790074841 43
1790074846 43
1790074851 43
1790074856 43
1790074861 43
1790074866 43
1790074871 43
1790074876 43
1790074881 43
1790074886 43
1790074891 43
1790074896 43
1790074901 48
1790074906 48
1790074911 48
1790074916 48
1790074921 48
1790074926 48
1790074931 48
1790074936 48
```
</details>

---

