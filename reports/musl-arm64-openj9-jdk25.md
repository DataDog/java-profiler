---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:52:31 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 14 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1794937489 52
1794937494 52
1794937499 52
1794937504 52
1794937509 52
1794937514 64
1794937519 64
1794937524 64
1794937529 64
1794937534 64
1794937539 64
1794937544 64
1794937549 64
1794937554 64
1794937559 64
1794937564 64
1794937569 64
1794937574 64
1794937579 64
1794937584 64
```
</details>

---

