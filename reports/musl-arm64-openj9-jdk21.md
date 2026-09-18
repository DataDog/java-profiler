---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:06:40 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 13 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743479 43
1789743484 43
1789743489 43
1789743494 43
1789743499 43
1789743504 43
1789743509 48
1789743514 48
1789743519 48
1789743524 48
1789743529 48
1789743534 48
1789743539 48
1789743544 48
1789743549 48
1789743554 48
1789743559 48
1789743564 48
1789743569 48
1789743574 48
```
</details>

---

