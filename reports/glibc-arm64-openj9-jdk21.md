---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:43:43 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794998255 46
1794998260 46
1794998265 46
1794998270 46
1794998275 46
1794998280 46
1794998285 46
1794998290 46
1794998295 46
1794998300 46
1794998305 46
1794998311 46
1794998316 46
1794998321 46
1794998326 46
1794998331 51
1794998336 51
1794998341 51
1794998346 51
1794998351 51
```
</details>

---

