---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 05:51:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1787132862 48
1787132867 48
1787132872 48
1787132877 48
1787132882 48
1787132887 48
1787132892 48
1787132897 48
1787132902 48
1787132907 48
1787132912 48
1787132917 48
1787132922 48
1787132927 44
1787132932 44
1787132937 44
1787132942 44
1787132947 44
1787132952 44
1787132957 44
```
</details>

---

