---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 09:54:55 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790257798 50
1790257803 50
1790257808 50
1790257813 50
1790257818 50
1790257823 50
1790257828 50
1790257833 50
1790257838 50
1790257843 50
1790257848 50
1790257853 50
1790257858 50
1790257863 50
1790257868 50
1790257873 50
1790257878 50
1790257883 50
1790257888 50
1790257893 50
```
</details>

---

