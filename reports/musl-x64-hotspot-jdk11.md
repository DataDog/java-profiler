---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 06:29:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792578298 96
1792578303 96
1792578308 96
1792578313 94
1792578318 94
1792578323 94
1792578328 94
1792578333 94
1792578338 94
1792578343 94
1792578348 94
1792578353 94
1792578358 94
1792578363 94
1792578368 94
1792578373 94
1792578378 94
1792578383 94
1792578388 94
1792578393 94
```
</details>

---

