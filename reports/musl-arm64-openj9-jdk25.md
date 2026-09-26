---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-26 01:03:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 11 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 33-43 cores)</summary>

```
1790398389 43
1790398394 43
1790398399 43
1790398404 43
1790398409 43
1790398414 43
1790398419 43
1790398424 43
1790398429 43
1790398434 43
1790398439 43
1790398444 43
1790398449 43
1790398454 43
1790398459 43
1790398464 43
1790398469 43
1790398474 43
1790398479 43
1790398484 43
```
</details>

---

