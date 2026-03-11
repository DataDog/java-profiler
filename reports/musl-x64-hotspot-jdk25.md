---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 05:23:34 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 13 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 60-70 cores)</summary>

```
1773220576 60
1773220581 60
1773220586 65
1773220591 65
1773220596 63
1773220601 63
1773220606 63
1773220611 65
1773220616 65
1773220621 65
1773220626 65
1773220631 70
1773220636 70
1773220641 70
1773220646 70
1773220651 70
1773220656 70
1773220661 70
1773220666 70
1773220671 70
```
</details>

---

