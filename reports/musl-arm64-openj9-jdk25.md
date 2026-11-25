---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 05:33:20 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795602422 64
1795602427 64
1795602432 64
1795602437 64
1795602442 64
1795602447 64
1795602452 64
1795602457 64
1795602462 64
1795602467 64
1795602472 64
1795602477 64
1795602482 64
1795602487 64
1795602492 64
1795602497 64
1795602502 64
1795602507 64
1795602512 64
1795602517 64
```
</details>

---

