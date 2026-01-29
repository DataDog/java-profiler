---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 07:49:58 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 17.27/sec |
| Health Score | 1079% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 24.13/sec |
| Health Score | 1508% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (6 unique values: 74-87 cores)</summary>

```
1769690651 85
1769690656 85
1769690661 87
1769690666 87
1769690671 87
1769690676 87
1769690681 87
1769690686 87
1769690691 87
1769690696 87
1769690701 87
1769690706 87
1769690711 87
1769690716 80
1769690721 80
1769690726 80
1769690731 80
1769690736 78
1769690741 78
1769690746 78
```
</details>

---

