---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 16:08:05 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1788292952 43
1788292957 43
1788292962 43
1788292967 38
1788292972 38
1788292977 38
1788292982 38
1788292987 38
1788292992 38
1788292997 38
1788293002 38
1788293007 43
1788293012 43
1788293017 43
1788293022 43
1788293027 43
1788293032 43
1788293037 43
1788293042 43
1788293047 43
```
</details>

---

