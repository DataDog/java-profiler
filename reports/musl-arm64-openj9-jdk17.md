---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 16:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 5 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1790193529 46
1790193534 46
1790193539 46
1790193544 46
1790193550 46
1790193555 46
1790193560 46
1790193565 48
1790193570 48
1790193575 48
1790193580 48
1790193585 48
1790193590 48
1790193595 48
1790193600 48
1790193605 48
1790193610 48
1790193615 48
1790193620 48
1790193625 48
```
</details>

---

