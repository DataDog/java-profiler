---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 12:31:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1787243206 94
1787243211 94
1787243216 94
1787243221 94
1787243226 94
1787243231 94
1787243236 94
1787243241 94
1787243246 94
1787243251 94
1787243256 92
1787243261 92
1787243266 92
1787243271 94
1787243276 94
1787243281 94
1787243286 94
1787243291 94
1787243296 86
1787243301 86
```
</details>

---

