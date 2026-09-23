---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 11:28:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 35-48 cores)</summary>

```
1790177005 48
1790177010 48
1790177015 48
1790177020 48
1790177025 48
1790177030 48
1790177035 48
1790177040 48
1790177045 48
1790177050 48
1790177055 48
1790177060 48
1790177065 48
1790177070 48
1790177075 48
1790177080 43
1790177085 43
1790177090 43
1790177095 43
1790177100 40
```
</details>

---

