---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:02:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794783536 53
1794783541 53
1794783546 53
1794783551 53
1794783556 53
1794783561 53
1794783566 53
1794783571 53
1794783576 53
1794783581 53
1794783586 53
1794783591 55
1794783596 55
1794783601 55
1794783606 55
1794783611 55
1794783616 55
1794783621 55
1794783626 55
1794783631 55
```
</details>

---

