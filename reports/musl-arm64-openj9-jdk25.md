---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:36:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1794407501 23
1794407506 23
1794407511 23
1794407516 23
1794407521 23
1794407526 23
1794407531 23
1794407536 23
1794407541 23
1794407546 23
1794407551 23
1794407556 23
1794407561 23
1794407566 23
1794407571 23
1794407576 23
1794407581 23
1794407586 28
1794407591 28
1794407596 28
```
</details>

---

