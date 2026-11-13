---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:55:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 56-69 cores)</summary>

```
1794574193 69
1794574198 69
1794574203 69
1794574208 69
1794574213 69
1794574218 69
1794574223 69
1794574228 69
1794574233 69
1794574238 56
1794574243 56
1794574248 56
1794574253 56
1794574258 58
1794574263 58
1794574268 58
1794574273 58
1794574278 58
1794574283 58
1794574288 58
```
</details>

---

