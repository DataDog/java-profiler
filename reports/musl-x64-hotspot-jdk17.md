---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:33:15 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 82-85 cores)</summary>

```
1795015591 83
1795015596 83
1795015601 83
1795015606 83
1795015611 83
1795015616 83
1795015621 83
1795015626 85
1795015631 85
1795015636 84
1795015641 84
1795015646 82
1795015651 82
1795015656 82
1795015661 82
1795015666 82
1795015671 82
1795015676 82
1795015681 82
1795015686 82
```
</details>

---

