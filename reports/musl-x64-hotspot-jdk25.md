---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 06:08:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1795172571 45
1795172576 45
1795172581 45
1795172586 45
1795172591 45
1795172596 43
1795172601 43
1795172606 43
1795172611 43
1795172616 43
1795172621 43
1795172626 43
1795172631 43
1795172636 43
1795172641 43
1795172646 43
1795172651 43
1795172656 43
1795172661 43
1795172666 43
```
</details>

---

