---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 06:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 63-66 cores)</summary>

```
1792578288 64
1792578293 64
1792578298 64
1792578303 64
1792578308 64
1792578313 64
1792578318 64
1792578323 64
1792578328 64
1792578333 64
1792578338 64
1792578343 64
1792578348 64
1792578353 64
1792578358 64
1792578363 64
1792578368 64
1792578373 66
1792578378 66
1792578383 63
```
</details>

---

