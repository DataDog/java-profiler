---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:01:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1794585439 31
1794585444 31
1794585449 31
1794585454 48
1794585459 48
1794585464 48
1794585469 48
1794585474 48
1794585479 48
1794585484 48
1794585489 48
1794585494 48
1794585499 48
1794585504 48
1794585509 48
1794585514 48
1794585519 48
1794585524 48
1794585529 48
1794585534 48
```
</details>

---

