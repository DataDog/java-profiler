---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-10 16:39:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 2 |
| Sample Rate | 0.03/sec |
| Health Score | 2% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794346504 48
1794346509 48
1794346514 48
1794346519 48
1794346524 48
1794346529 48
1794346534 48
1794346539 48
1794346544 48
1794346549 48
1794346554 48
1794346559 48
1794346564 48
1794346569 48
1794346574 48
1794346579 48
1794346584 48
1794346589 48
1794346595 48
1794346600 48
```
</details>

---

