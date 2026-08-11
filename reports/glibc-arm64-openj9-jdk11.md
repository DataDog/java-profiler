---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 14:11:47 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 19-30 cores)</summary>

```
1786471632 19
1786471637 19
1786471642 19
1786471647 19
1786471652 19
1786471657 19
1786471662 19
1786471667 19
1786471672 30
1786471677 30
1786471682 30
1786471687 30
1786471692 30
1786471697 30
1786471702 19
1786471707 19
1786471712 19
1786471717 19
1786471722 19
1786471727 19
```
</details>

---

