---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 09:23:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 11 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1787404793 36
1787404798 36
1787404803 36
1787404808 36
1787404813 36
1787404818 36
1787404823 36
1787404828 36
1787404833 36
1787404838 36
1787404843 36
1787404848 36
1787404853 36
1787404858 34
1787404863 34
1787404868 34
1787404873 34
1787404878 34
1787404883 34
1787404888 34
```
</details>

---

