---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 05:15:18 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790327356 50
1790327361 50
1790327366 50
1790327371 50
1790327376 50
1790327381 50
1790327386 50
1790327391 50
1790327396 50
1790327401 50
1790327406 50
1790327411 50
1790327416 50
1790327421 50
1790327426 50
1790327431 50
1790327436 50
1790327441 50
1790327446 50
1790327451 50
```
</details>

---

