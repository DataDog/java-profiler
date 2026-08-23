---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-23 00:55:50 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 78 |

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

