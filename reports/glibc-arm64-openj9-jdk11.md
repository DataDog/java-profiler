---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:56:28 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789677904 46
1789677909 46
1789677914 46
1789677919 46
1789677924 46
1789677929 46
1789677934 46
1789677939 46
1789677944 46
1789677949 46
1789677955 46
1789677960 46
1789677965 46
1789677970 46
1789677975 46
1789677980 46
1789677985 48
1789677990 48
1789677995 48
1789678000 48
```
</details>

---

