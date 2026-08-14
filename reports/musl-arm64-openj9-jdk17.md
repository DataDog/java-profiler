---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-14 08:29:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786710264 46
1786710269 46
1786710274 46
1786710279 46
1786710284 46
1786710289 46
1786710294 46
1786710299 46
1786710304 46
1786710309 46
1786710314 48
1786710319 48
1786710324 48
1786710329 48
1786710334 48
1786710339 48
1786710344 48
1786710349 48
1786710354 48
1786710359 48
```
</details>

---

