---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 12:53:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 74-79 cores)</summary>

```
1794592183 77
1794592188 77
1794592193 77
1794592198 75
1794592203 75
1794592208 75
1794592213 75
1794592218 75
1794592223 75
1794592228 75
1794592233 75
1794592238 75
1794592243 75
1794592248 75
1794592253 79
1794592258 79
1794592263 79
1794592268 76
1794592273 76
1794592278 76
```
</details>

---

