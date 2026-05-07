---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:39:47 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 56-57 cores)</summary>

```
1778171762 57
1778171767 57
1778171772 56
1778171777 56
1778171782 56
1778171787 56
1778171792 56
1778171797 56
1778171802 56
1778171807 56
1778171812 57
1778171817 57
1778171822 57
1778171827 57
1778171832 57
1778171837 57
1778171842 57
1778171847 57
1778171852 57
1778171857 57
```
</details>

---

