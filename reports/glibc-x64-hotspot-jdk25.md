---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-12 10:15:07 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 991 |
| Sample Rate | 16.52/sec |
| Health Score | 1032% |
| Threads | 12 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770908960 28
1770908965 28
1770908970 28
1770908975 28
1770908980 28
1770908985 28
1770908990 28
1770908995 28
1770909000 28
1770909005 28
1770909010 28
1770909015 32
1770909020 32
1770909025 32
1770909030 32
1770909035 32
1770909040 27
1770909045 27
1770909050 27
1770909055 27
```
</details>

---

