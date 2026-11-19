---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:27:31 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 58-69 cores)</summary>

```
1795112611 58
1795112616 69
1795112621 69
1795112626 69
1795112631 69
1795112636 69
1795112641 69
1795112646 69
1795112651 69
1795112656 67
1795112661 67
1795112666 67
1795112671 65
1795112676 65
1795112681 65
1795112686 65
1795112691 65
1795112696 65
1795112701 67
1795112706 67
```
</details>

---

