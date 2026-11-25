---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:36:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 437 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 59-68 cores)</summary>

```
1795620718 59
1795620723 59
1795620728 59
1795620733 59
1795620738 68
1795620743 68
1795620748 68
1795620753 68
1795620758 68
1795620763 68
1795620768 68
1795620773 68
1795620778 68
1795620783 68
1795620788 68
1795620793 68
1795620798 68
1795620803 68
1795620808 68
1795620813 68
```
</details>

---

