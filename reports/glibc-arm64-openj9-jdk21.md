---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:39:36 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791531272 48
1791531277 48
1791531282 48
1791531287 48
1791531292 48
1791531297 48
1791531302 43
1791531307 43
1791531312 43
1791531317 43
1791531322 43
1791531327 43
1791531332 43
1791531337 43
1791531342 43
1791531347 43
1791531352 43
1791531357 43
1791531362 48
1791531367 48
```
</details>

---

