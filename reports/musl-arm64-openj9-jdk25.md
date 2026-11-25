---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:52:59 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1795614509 47
1795614514 47
1795614519 47
1795614524 47
1795614530 47
1795614535 45
1795614540 45
1795614545 45
1795614550 45
1795614555 45
1795614560 45
1795614565 45
1795614570 45
1795614575 45
1795614580 47
1795614585 47
1795614590 47
1795614595 47
1795614600 47
1795614605 47
```
</details>

---

