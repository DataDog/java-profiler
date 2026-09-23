---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:03:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (6 unique values: 33-48 cores)</summary>

```
1790193547 48
1790193552 48
1790193557 48
1790193562 43
1790193567 43
1790193572 43
1790193577 43
1790193582 43
1790193587 43
1790193592 43
1790193597 43
1790193602 38
1790193607 38
1790193612 38
1790193617 33
1790193622 33
1790193627 38
1790193632 38
1790193637 38
1790193642 38
```
</details>

---

