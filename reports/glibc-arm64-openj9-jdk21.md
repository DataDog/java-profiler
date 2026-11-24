---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795529376 38
1795529381 38
1795529386 38
1795529391 38
1795529396 38
1795529401 43
1795529406 43
1795529411 43
1795529416 43
1795529421 43
1795529426 43
1795529431 43
1795529436 43
1795529441 43
1795529446 43
1795529451 43
1795529456 43
1795529461 43
1795529466 43
1795529471 43
```
</details>

---

