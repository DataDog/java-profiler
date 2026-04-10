---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-10 06:00:36 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 85-93 cores)</summary>

```
1775814857 85
1775814862 85
1775814867 85
1775814872 85
1775814877 85
1775814882 85
1775814887 85
1775814892 85
1775814897 85
1775814902 85
1775814907 85
1775814912 85
1775814917 85
1775814922 85
1775814927 89
1775814932 89
1775814937 89
1775814942 89
1775814947 89
1775814952 93
```
</details>

---

