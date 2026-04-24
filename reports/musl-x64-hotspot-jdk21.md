---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:31:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 45-87 cores)</summary>

```
1777033576 87
1777033581 87
1777033586 87
1777033591 87
1777033596 87
1777033601 87
1777033606 87
1777033611 87
1777033616 87
1777033621 87
1777033626 87
1777033631 87
1777033636 50
1777033641 50
1777033646 50
1777033651 50
1777033656 50
1777033661 50
1777033666 50
1777033671 50
```
</details>

---

