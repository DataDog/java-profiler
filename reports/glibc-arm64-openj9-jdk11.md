---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:31:32 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 41-41 cores)</summary>

```
1790093979 41
1790093984 41
1790093989 41
1790093994 41
1790093999 41
1790094004 41
1790094009 41
1790094014 41
1790094019 41
1790094024 41
1790094029 41
1790094034 41
1790094039 41
1790094044 41
1790094049 41
1790094054 41
1790094059 41
1790094064 41
1790094069 41
1790094074 41
```
</details>

---

