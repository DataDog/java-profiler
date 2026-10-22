---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 06:46:59 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792665790 28
1792665795 28
1792665800 28
1792665805 28
1792665810 28
1792665815 28
1792665820 30
1792665825 30
1792665830 30
1792665835 30
1792665840 30
1792665845 30
1792665850 30
1792665855 30
1792665860 30
1792665865 30
1792665870 30
1792665875 30
1792665880 30
1792665885 30
```
</details>

---

