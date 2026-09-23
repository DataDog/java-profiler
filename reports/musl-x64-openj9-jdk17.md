---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:06:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (6 unique values: 37-49 cores)</summary>

```
1790168530 49
1790168535 49
1790168540 49
1790168545 49
1790168550 45
1790168555 45
1790168560 45
1790168565 45
1790168570 45
1790168575 45
1790168580 45
1790168585 45
1790168590 39
1790168595 39
1790168600 39
1790168605 39
1790168610 39
1790168615 37
1790168620 37
1790168625 37
```
</details>

---

