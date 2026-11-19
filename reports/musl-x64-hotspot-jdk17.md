---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:23:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 57-96 cores)</summary>

```
1795108623 57
1795108628 57
1795108633 57
1795108638 57
1795108643 57
1795108648 77
1795108653 77
1795108658 77
1795108663 77
1795108668 77
1795108673 77
1795108678 77
1795108683 77
1795108688 77
1795108693 96
1795108698 96
1795108703 96
1795108708 96
1795108713 96
1795108718 96
```
</details>

---

