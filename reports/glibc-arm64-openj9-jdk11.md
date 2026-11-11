---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:05:54 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794391206 38
1794391211 38
1794391216 38
1794391221 38
1794391226 38
1794391231 38
1794391236 38
1794391241 38
1794391246 38
1794391251 38
1794391256 38
1794391261 38
1794391266 38
1794391271 38
1794391276 38
1794391281 38
1794391286 38
1794391291 38
1794391296 38
1794391301 43
```
</details>

---

