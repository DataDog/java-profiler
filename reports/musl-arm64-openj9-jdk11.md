---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:17 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793800907 47
1793800912 47
1793800918 47
1793800923 47
1793800928 47
1793800933 47
1793800938 47
1793800943 48
1793800948 48
1793800953 48
1793800958 48
1793800963 48
1793800968 48
1793800973 48
1793800978 48
1793800983 48
1793800988 48
1793800993 48
1793800998 48
1793801003 48
```
</details>

---

