---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:20:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1134 |
| Sample Rate | 18.90/sec |
| Health Score | 1181% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 67-77 cores)</summary>

```
1776694334 67
1776694339 67
1776694344 71
1776694349 71
1776694354 71
1776694359 71
1776694364 71
1776694369 71
1776694374 71
1776694379 71
1776694384 71
1776694389 75
1776694394 75
1776694399 75
1776694404 75
1776694409 75
1776694414 77
1776694419 77
1776694424 77
1776694429 77
```
</details>

---

