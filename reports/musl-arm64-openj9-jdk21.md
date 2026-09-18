---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:39:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 15 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (3 unique values: 7-19 cores)</summary>

```
1789716540 12
1789716545 12
1789716550 7
1789716555 7
1789716560 7
1789716565 7
1789716570 7
1789716575 7
1789716580 7
1789716585 7
1789716590 7
1789716595 7
1789716600 19
1789716605 19
1789716610 19
1789716615 19
1789716620 19
1789716625 19
1789716630 19
1789716635 19
```
</details>

---

