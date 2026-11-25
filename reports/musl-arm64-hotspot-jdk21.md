---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:37:25 EST

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
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 9 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795613594 47
1795613599 47
1795613604 47
1795613609 47
1795613614 47
1795613619 47
1795613624 47
1795613629 47
1795613634 47
1795613639 47
1795613644 47
1795613649 47
1795613654 47
1795613659 47
1795613664 42
1795613669 42
1795613674 42
1795613679 42
1795613684 42
1795613689 42
```
</details>

---

