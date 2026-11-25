---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795605440 64
1795605445 64
1795605450 64
1795605455 64
1795605460 64
1795605465 64
1795605470 64
1795605475 64
1795605480 64
1795605485 64
1795605490 64
1795605495 64
1795605500 64
1795605505 64
1795605510 64
1795605515 60
1795605520 60
1795605525 60
1795605530 60
1795605535 60
```
</details>

---

