---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:05:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (1 unique values: 8-8 cores)</summary>

```
1789743564 8
1789743569 8
1789743574 8
1789743579 8
1789743584 8
1789743589 8
1789743594 8
1789743599 8
1789743604 8
1789743609 8
1789743614 8
1789743619 8
1789743624 8
1789743629 8
1789743634 8
1789743639 8
1789743644 8
1789743649 8
1789743654 8
1789743659 8
```
</details>

---

