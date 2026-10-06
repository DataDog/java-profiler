---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-06 10:08:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791295392 40
1791295397 40
1791295402 40
1791295407 40
1791295412 40
1791295417 40
1791295422 40
1791295427 40
1791295432 40
1791295437 40
1791295442 40
1791295447 40
1791295452 40
1791295457 40
1791295462 40
1791295467 40
1791295472 40
1791295477 40
1791295482 40
1791295487 40
```
</details>

---

