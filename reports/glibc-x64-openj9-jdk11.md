---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 14:43:11 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 37-63 cores)</summary>

```
1777487760 37
1777487765 37
1777487770 37
1777487775 37
1777487780 37
1777487785 37
1777487790 37
1777487795 37
1777487800 37
1777487805 37
1777487810 39
1777487815 39
1777487820 39
1777487825 39
1777487830 39
1777487835 39
1777487840 39
1777487845 39
1777487850 39
1777487855 63
```
</details>

---

