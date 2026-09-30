---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 13:02:41 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790787392 64
1790787397 64
1790787402 64
1790787407 64
1790787412 64
1790787417 64
1790787422 64
1790787427 64
1790787432 64
1790787437 64
1790787442 64
1790787447 64
1790787452 64
1790787457 64
1790787462 64
1790787467 64
1790787472 64
1790787477 64
1790787482 64
1790787487 64
```
</details>

---

