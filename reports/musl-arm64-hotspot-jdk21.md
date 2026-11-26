---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:28:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (5 unique values: 39-59 cores)</summary>

```
1795706619 47
1795706624 47
1795706629 47
1795706634 47
1795706639 42
1795706644 42
1795706649 59
1795706654 59
1795706659 59
1795706664 59
1795706669 59
1795706674 59
1795706679 39
1795706684 39
1795706689 39
1795706694 39
1795706700 39
1795706705 39
1795706710 39
1795706715 39
```
</details>

---

