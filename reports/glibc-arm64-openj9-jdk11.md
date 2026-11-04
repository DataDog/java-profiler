---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793800943 29
1793800948 29
1793800953 29
1793800958 29
1793800963 29
1793800968 29
1793800973 29
1793800978 29
1793800983 29
1793800988 29
1793800993 29
1793800998 29
1793801003 29
1793801008 29
1793801013 29
1793801018 29
1793801023 29
1793801028 34
1793801033 34
1793801038 29
```
</details>

---

