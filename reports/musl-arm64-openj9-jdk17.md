---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 06:41:34 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1791283015 64
1791283020 64
1791283025 64
1791283030 64
1791283035 64
1791283040 64
1791283045 64
1791283050 64
1791283055 64
1791283060 64
1791283065 64
1791283070 64
1791283075 64
1791283080 64
1791283085 59
1791283090 59
1791283095 59
1791283100 59
1791283105 59
1791283110 59
```
</details>

---

