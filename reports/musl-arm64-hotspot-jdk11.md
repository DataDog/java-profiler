---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:30:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1029 |
| Sample Rate | 17.15/sec |
| Health Score | 1072% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795112629 50
1795112634 50
1795112639 50
1795112644 50
1795112649 50
1795112654 50
1795112659 50
1795112664 50
1795112669 50
1795112674 50
1795112679 50
1795112684 50
1795112689 50
1795112694 50
1795112699 50
1795112705 50
1795112710 45
1795112715 45
1795112720 45
1795112725 45
```
</details>

---

