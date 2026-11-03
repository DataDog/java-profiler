---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:25:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 72-86 cores)</summary>

```
1793722930 73
1793722935 73
1793722940 73
1793722945 74
1793722950 74
1793722955 74
1793722960 74
1793722965 74
1793722970 74
1793722975 74
1793722980 74
1793722985 74
1793722990 72
1793722995 72
1793723000 72
1793723005 72
1793723010 72
1793723015 72
1793723020 72
1793723025 72
```
</details>

---

