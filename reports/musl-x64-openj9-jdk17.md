---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 04:59:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1794477197 71
1794477202 71
1794477207 71
1794477212 71
1794477217 71
1794477222 71
1794477227 71
1794477232 71
1794477237 71
1794477242 71
1794477247 71
1794477252 71
1794477257 71
1794477262 71
1794477267 71
1794477272 71
1794477277 71
1794477282 71
1794477287 71
1794477292 73
```
</details>

---

