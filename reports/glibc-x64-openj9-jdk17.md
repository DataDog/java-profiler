---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-12 11:39:21 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 12 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 73-92 cores)</summary>

```
1773329616 79
1773329621 79
1773329626 79
1773329631 79
1773329636 92
1773329641 92
1773329646 92
1773329651 92
1773329656 92
1773329661 92
1773329666 92
1773329671 92
1773329676 92
1773329681 92
1773329686 92
1773329691 92
1773329696 83
1773329701 83
1773329706 83
1773329711 83
```
</details>

---

