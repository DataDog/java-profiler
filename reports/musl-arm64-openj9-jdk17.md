---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 06:08:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 31-45 cores)</summary>

```
1795172581 45
1795172586 45
1795172591 45
1795172596 45
1795172601 45
1795172606 45
1795172611 45
1795172616 45
1795172621 45
1795172626 45
1795172631 45
1795172636 45
1795172641 45
1795172646 45
1795172651 45
1795172656 31
1795172661 31
1795172666 31
1795172671 31
1795172676 31
```
</details>

---

