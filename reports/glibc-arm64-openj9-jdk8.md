---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-01 14:09:09 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788285894 43
1788285899 43
1788285904 43
1788285909 43
1788285914 43
1788285919 43
1788285924 43
1788285929 48
1788285934 48
1788285939 43
1788285944 43
1788285949 43
1788285954 43
1788285959 43
1788285964 43
1788285969 43
1788285974 43
1788285979 43
1788285984 43
1788285989 43
```
</details>

---

