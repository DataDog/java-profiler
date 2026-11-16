---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:34:13 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 14 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794850203 48
1794850208 48
1794850213 48
1794850218 48
1794850223 48
1794850228 48
1794850233 48
1794850238 48
1794850243 48
1794850248 48
1794850253 48
1794850258 48
1794850263 48
1794850268 48
1794850273 48
1794850278 48
1794850283 48
1794850288 48
1794850293 48
1794850298 48
```
</details>

---

