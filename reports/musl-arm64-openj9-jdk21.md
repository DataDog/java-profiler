---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
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
1795605540 60
1795605545 60
1795605550 60
1795605555 60
1795605560 60
```
</details>

---

