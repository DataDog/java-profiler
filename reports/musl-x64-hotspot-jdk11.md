---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 77-96 cores)</summary>

```
1789743328 77
1789743333 77
1789743338 77
1789743343 77
1789743348 77
1789743353 77
1789743358 77
1789743363 77
1789743368 77
1789743373 77
1789743378 77
1789743383 77
1789743388 77
1789743393 77
1789743398 79
1789743403 79
1789743408 79
1789743413 79
1789743418 96
1789743423 96
```
</details>

---

