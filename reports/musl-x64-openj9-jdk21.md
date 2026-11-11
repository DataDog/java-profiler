---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:36:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 89-93 cores)</summary>

```
1794407491 90
1794407496 90
1794407501 90
1794407506 92
1794407511 92
1794407516 92
1794407521 92
1794407526 92
1794407531 92
1794407536 89
1794407541 89
1794407546 89
1794407551 89
1794407556 89
1794407561 89
1794407566 89
1794407571 91
1794407576 91
1794407581 91
1794407586 91
```
</details>

---

