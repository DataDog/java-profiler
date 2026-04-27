---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 14:34:06 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 10 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777314574 64
1777314579 64
1777314584 64
1777314589 64
1777314594 64
1777314599 64
1777314604 64
1777314609 64
1777314614 64
1777314619 64
1777314624 64
1777314629 64
1777314634 64
1777314639 64
1777314644 64
1777314649 64
1777314654 64
1777314659 64
1777314664 64
1777314669 64
```
</details>

---

