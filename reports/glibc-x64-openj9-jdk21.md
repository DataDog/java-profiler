---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:31:40 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 8-34 cores)</summary>

```
1795397219 34
1795397224 34
1795397229 34
1795397234 34
1795397239 17
1795397244 17
1795397249 17
1795397254 17
1795397259 17
1795397264 17
1795397269 34
1795397274 34
1795397279 8
1795397284 8
1795397289 8
1795397294 8
1795397299 8
1795397304 8
1795397309 8
1795397314 8
```
</details>

---

