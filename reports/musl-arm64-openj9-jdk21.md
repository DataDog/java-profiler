---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:31:29 EST

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795530260 64
1795530265 64
1795530270 64
1795530275 64
1795530280 64
1795530285 64
1795530290 64
1795530295 64
1795530300 64
1795530305 64
1795530310 64
1795530315 64
1795530320 64
1795530325 64
1795530330 59
1795530335 59
1795530340 59
1795530345 59
1795530350 59
1795530355 59
```
</details>

---

