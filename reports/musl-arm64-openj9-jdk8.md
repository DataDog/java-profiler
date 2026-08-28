---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-28 08:40:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1787920555 29
1787920560 29
1787920565 29
1787920570 29
1787920575 34
1787920580 34
1787920585 32
1787920590 32
1787920595 32
1787920600 32
1787920605 32
1787920610 32
1787920615 32
1787920620 32
1787920625 32
1787920630 32
1787920635 32
1787920640 34
1787920646 34
1787920651 34
```
</details>

---

