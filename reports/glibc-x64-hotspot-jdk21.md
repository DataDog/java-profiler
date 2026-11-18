---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:38:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 88-91 cores)</summary>

```
1795001623 91
1795001628 91
1795001633 91
1795001638 91
1795001643 91
1795001648 91
1795001653 91
1795001658 91
1795001663 91
1795001668 91
1795001673 91
1795001678 91
1795001683 91
1795001688 91
1795001693 91
1795001698 91
1795001703 91
1795001708 91
1795001713 91
1795001718 88
```
</details>

---

