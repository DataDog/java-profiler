---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 05:17:23 EDT

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
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792141944 43
1792141949 43
1792141954 43
1792141959 43
1792141964 43
1792141969 43
1792141974 48
1792141979 48
1792141984 48
1792141989 48
1792141994 48
1792141999 48
1792142004 48
1792142009 48
1792142014 48
1792142019 48
1792142024 48
1792142029 48
1792142034 48
1792142039 48
```
</details>

---

