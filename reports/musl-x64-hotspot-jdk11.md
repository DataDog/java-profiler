---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:30:05 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (4 unique values: 48-58 cores)</summary>

```
1795112631 56
1795112636 56
1795112641 56
1795112646 56
1795112651 56
1795112656 56
1795112661 56
1795112666 56
1795112671 56
1795112676 56
1795112681 54
1795112686 54
1795112691 54
1795112696 54
1795112701 56
1795112706 56
1795112711 56
1795112716 56
1795112721 56
1795112726 56
```
</details>

---

