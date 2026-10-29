---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 08:13:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 65-79 cores)</summary>

```
1793275666 79
1793275671 79
1793275676 79
1793275681 79
1793275686 79
1793275691 79
1793275696 79
1793275701 79
1793275706 79
1793275711 79
1793275716 79
1793275721 79
1793275726 79
1793275731 77
1793275736 77
1793275741 65
1793275746 65
1793275751 65
1793275756 65
1793275761 65
```
</details>

---

