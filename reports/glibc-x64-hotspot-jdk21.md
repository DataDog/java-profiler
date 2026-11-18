---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:34:31 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1795015822 26
1795015827 26
1795015832 26
1795015837 26
1795015842 26
1795015847 26
1795015852 26
1795015857 26
1795015862 26
1795015867 26
1795015872 26
1795015877 28
1795015882 28
1795015887 28
1795015892 28
1795015897 28
1795015902 28
1795015907 28
1795015912 28
1795015917 30
```
</details>

---

