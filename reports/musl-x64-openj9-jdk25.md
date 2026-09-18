---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 12:42:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1789749361 88
1789749366 88
1789749371 88
1789749376 88
1789749381 88
1789749386 88
1789749391 90
1789749396 90
1789749401 92
1789749406 92
1789749411 94
1789749416 94
1789749421 94
1789749426 96
1789749431 96
1789749436 96
1789749441 96
1789749446 94
1789749451 94
1789749456 94
```
</details>

---

