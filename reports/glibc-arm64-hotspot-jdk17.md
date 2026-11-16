---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:41:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 9 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794832688 36
1794832693 36
1794832698 36
1794832703 36
1794832708 36
1794832713 36
1794832718 36
1794832723 48
1794832728 48
1794832733 48
1794832738 48
1794832743 48
1794832748 48
1794832753 36
1794832758 36
1794832763 36
1794832768 36
1794832773 36
1794832778 36
1794832783 36
```
</details>

---

