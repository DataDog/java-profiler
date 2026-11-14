---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:57:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 10 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794682400 96
1794682405 96
1794682410 94
1794682416 94
1794682421 94
1794682426 94
1794682431 94
1794682436 94
1794682441 94
1794682446 94
1794682451 94
1794682456 94
1794682461 94
1794682466 94
1794682471 96
1794682476 96
1794682481 96
1794682486 96
1794682491 96
1794682496 96
```
</details>

---

