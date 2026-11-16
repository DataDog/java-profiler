---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:41:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1794832703 46
1794832708 46
1794832713 44
1794832718 44
1794832723 44
1794832728 44
1794832733 44
1794832738 44
1794832743 44
1794832748 44
1794832753 44
1794832758 44
1794832763 44
1794832768 44
1794832773 46
1794832778 46
1794832783 46
1794832788 46
1794832793 46
1794832798 46
```
</details>

---

