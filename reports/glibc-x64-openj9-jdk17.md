---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 04:59:12 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 25-32 cores)</summary>

```
1794477211 25
1794477216 25
1794477221 25
1794477226 25
1794477231 25
1794477236 25
1794477241 25
1794477246 25
1794477251 25
1794477256 25
1794477261 25
1794477266 25
1794477271 25
1794477276 25
1794477281 25
1794477286 25
1794477291 25
1794477296 25
1794477301 32
1794477306 32
```
</details>

---

