---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-06 10:50:47 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 32-68 cores)</summary>

```
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
1770392803 36
1770392808 36
1770392813 36
```
</details>

---

