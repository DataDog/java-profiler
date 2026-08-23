---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-23 00:55:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 30-36 cores)</summary>

```
1787460695 30
1787460700 30
1787460705 30
1787460710 32
1787460715 32
1787460720 32
1787460725 34
1787460730 34
1787460735 32
1787460740 32
1787460745 32
1787460750 32
1787460755 32
1787460760 32
1787460765 32
1787460770 32
1787460775 36
1787460780 36
1787460785 36
1787460790 36
```
</details>

---

