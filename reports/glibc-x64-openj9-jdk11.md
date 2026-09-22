---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 9-21 cores)</summary>

```
1790096704 11
1790096709 11
1790096714 11
1790096719 11
1790096724 11
1790096729 11
1790096734 11
1790096739 11
1790096744 11
1790096749 11
1790096754 11
1790096759 11
1790096764 11
1790096769 11
1790096774 11
1790096779 21
1790096784 21
1790096789 21
1790096794 21
1790096799 9
```
</details>

---

