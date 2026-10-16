---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792139935 30
1792139940 30
1792139945 30
1792139950 30
1792139955 30
1792139960 30
1792139965 30
1792139970 32
1792139975 32
1792139980 32
1792139985 32
1792139990 32
1792139995 32
1792140000 32
1792140005 32
1792140010 32
1792140015 32
1792140020 32
1792140025 32
1792140030 32
```
</details>

---

