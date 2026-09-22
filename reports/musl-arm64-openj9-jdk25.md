---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:32:54 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790093947 48
1790093952 48
1790093957 48
1790093962 48
1790093967 48
1790093972 48
1790093977 43
1790093982 43
1790093987 43
1790093992 43
1790093997 43
1790094002 43
1790094007 43
1790094012 43
1790094017 43
1790094022 43
1790094027 43
1790094032 43
1790094037 43
1790094042 43
```
</details>

---

