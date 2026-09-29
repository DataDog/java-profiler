---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 09:12:08 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 30-71 cores)</summary>

```
1790687090 30
1790687095 30
1790687100 30
1790687105 30
1790687110 30
1790687115 69
1790687120 69
1790687125 69
1790687130 69
1790687135 71
1790687140 71
1790687145 71
1790687150 71
1790687155 71
1790687160 71
1790687165 71
1790687170 71
1790687175 71
1790687180 71
1790687185 71
```
</details>

---

