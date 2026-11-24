---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 10:24:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1026 |
| Sample Rate | 17.10/sec |
| Health Score | 1069% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 48-60 cores)</summary>

```
1795533410 60
1795533415 60
1795533420 60
1795533425 60
1795533430 60
1795533435 60
1795533440 60
1795533445 60
1795533450 60
1795533455 60
1795533460 60
1795533465 60
1795533470 60
1795533475 60
1795533480 60
1795533485 48
1795533490 48
1795533495 48
1795533500 48
1795533505 48
```
</details>

---

