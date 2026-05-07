---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:39:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 60-68 cores)</summary>

```
1778171732 60
1778171737 62
1778171742 62
1778171747 62
1778171752 62
1778171757 62
1778171762 62
1778171767 64
1778171772 64
1778171777 64
1778171782 64
1778171787 64
1778171792 64
1778171797 64
1778171802 68
1778171807 68
1778171812 68
1778171817 68
1778171822 68
1778171827 68
```
</details>

---

