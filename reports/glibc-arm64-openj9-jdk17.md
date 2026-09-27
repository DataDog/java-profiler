---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-27 05:47:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (5 unique values: 14-34 cores)</summary>

```
1790502220 14
1790502225 14
1790502230 14
1790502235 14
1790502240 19
1790502245 19
1790502250 19
1790502255 19
1790502260 19
1790502265 19
1790502270 19
1790502275 19
1790502280 19
1790502285 19
1790502290 24
1790502295 24
1790502300 29
1790502305 29
1790502310 29
1790502315 29
```
</details>

---

