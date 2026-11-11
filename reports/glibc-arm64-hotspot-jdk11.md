---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:36:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794407491 43
1794407496 43
1794407501 43
1794407506 43
1794407511 43
1794407516 43
1794407521 43
1794407526 43
1794407531 43
1794407536 43
1794407541 43
1794407546 48
1794407551 48
1794407556 48
1794407561 48
1794407566 48
1794407571 48
1794407576 48
1794407581 48
1794407586 48
```
</details>

---

