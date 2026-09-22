---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:27:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 10 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 27-64 cores)</summary>

```
1790093984 27
1790093989 27
1790093994 27
1790093999 27
1790094004 27
1790094009 27
1790094014 27
1790094019 27
1790094024 27
1790094029 27
1790094034 27
1790094039 27
1790094044 27
1790094049 27
1790094054 27
1790094059 27
1790094064 27
1790094069 64
1790094074 64
1790094079 64
```
</details>

---

