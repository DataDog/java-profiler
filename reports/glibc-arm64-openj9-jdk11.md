---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 03:32:39 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793780938 40
1793780943 40
1793780948 40
1793780953 40
1793780958 40
1793780963 40
1793780968 40
1793780973 40
1793780978 40
1793780983 40
1793780988 40
1793780993 40
1793780998 40
1793781003 40
1793781008 40
1793781013 40
1793781018 40
1793781023 40
1793781028 40
1793781033 40
```
</details>

---

