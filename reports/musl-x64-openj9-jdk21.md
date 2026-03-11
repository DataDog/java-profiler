---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 12 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 68-93 cores)</summary>

```
1773250200 93
1773250205 93
1773250210 93
1773250215 93
1773250220 93
1773250225 93
1773250230 93
1773250235 93
1773250240 93
1773250245 93
1773250250 93
1773250255 93
1773250260 93
1773250265 93
1773250270 93
1773250275 93
1773250280 93
1773250285 68
1773250290 68
1773250295 68
```
</details>

---

