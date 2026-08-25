---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-25 11:03:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1787669817 44
1787669822 44
1787669827 44
1787669832 44
1787669837 44
1787669842 46
1787669847 46
1787669852 46
1787669857 41
1787669862 41
1787669867 41
1787669872 41
1787669877 41
1787669882 41
1787669887 43
1787669892 43
1787669897 43
1787669902 48
1787669907 48
1787669912 48
```
</details>

---

