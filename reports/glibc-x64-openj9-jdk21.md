---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 06:08:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795172591 62
1795172596 62
1795172601 62
1795172606 62
1795172611 62
1795172616 62
1795172621 62
1795172626 62
1795172631 62
1795172636 62
1795172641 62
1795172646 62
1795172651 64
1795172656 64
1795172661 64
1795172666 64
1795172671 64
1795172676 64
1795172681 64
1795172686 64
```
</details>

---

