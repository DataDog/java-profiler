---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-06 10:50:46 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 32-68 cores)</summary>

```
1770392703 34
1770392708 34
1770392713 34
1770392718 34
1770392723 34
1770392728 34
1770392733 34
1770392738 34
1770392743 34
1770392748 32
1770392753 32
1770392758 32
1770392763 32
1770392768 32
1770392773 32
1770392778 36
1770392783 36
1770392788 36
1770392793 36
1770392798 36
```
</details>

---

