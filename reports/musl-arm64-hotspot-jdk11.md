---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:28:35 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (5 unique values: 39-59 cores)</summary>

```
1795706619 47
1795706625 47
1795706630 47
1795706635 47
1795706640 42
1795706645 42
1795706650 59
1795706655 59
1795706660 59
1795706665 59
1795706670 59
1795706675 59
1795706680 39
1795706685 39
1795706690 39
1795706695 39
1795706700 39
1795706705 39
1795706710 39
1795706715 39
```
</details>

---

