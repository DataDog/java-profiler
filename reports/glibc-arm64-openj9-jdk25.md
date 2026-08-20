---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 10:46:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787236933 43
1787236938 43
1787236943 43
1787236948 43
1787236954 43
1787236959 43
1787236964 43
1787236969 48
1787236974 48
1787236979 48
1787236984 48
1787236989 48
1787236994 43
1787236999 43
1787237004 43
1787237009 43
1787237014 43
1787237019 43
1787237024 43
1787237029 43
```
</details>

---

