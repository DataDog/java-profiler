---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 63-87 cores)</summary>

```
1790093980 72
1790093985 72
1790093990 72
1790093995 72
1790094000 63
1790094005 63
1790094010 63
1790094015 63
1790094020 63
1790094025 63
1790094030 63
1790094035 63
1790094040 63
1790094045 63
1790094050 63
1790094055 63
1790094060 63
1790094065 63
1790094070 63
1790094075 63
```
</details>

---

