---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 09:35:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1793280622 32
1793280627 11
1793280632 11
1793280637 11
1793280642 11
1793280647 11
1793280652 11
1793280657 11
1793280662 11
1793280667 11
1793280672 11
1793280677 11
1793280682 11
1793280687 11
1793280692 11
1793280697 11
1793280702 11
1793280707 11
1793280712 11
1793280717 11
```
</details>

---

