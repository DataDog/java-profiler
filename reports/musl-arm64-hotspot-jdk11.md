---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-23 00:55:49 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787460700 48
1787460705 48
1787460710 43
1787460715 43
1787460720 43
1787460725 43
1787460730 43
1787460735 43
1787460740 43
1787460745 43
1787460750 43
1787460755 43
1787460760 43
1787460765 43
1787460770 43
1787460775 43
1787460780 43
1787460785 43
1787460790 43
1787460795 43
```
</details>

---

