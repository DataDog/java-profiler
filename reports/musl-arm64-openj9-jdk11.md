---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 07:56:31 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 8 |
| Allocations | 214 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1786103464 19
1786103469 19
1786103474 19
1786103479 19
1786103484 19
1786103489 19
1786103494 19
1786103499 19
1786103504 19
1786103509 19
1786103514 19
1786103519 19
1786103524 19
1786103529 19
1786103534 19
1786103539 19
1786103544 19
1786103549 19
1786103554 32
1786103559 32
```
</details>

---

