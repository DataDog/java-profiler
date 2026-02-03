---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 10:07:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 12 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (6 unique values: 50-82 cores)</summary>

```
1770130802 60
1770130807 50
1770130812 50
1770130817 52
1770130822 52
1770130828 76
1770130833 76
1770130838 76
1770130843 76
1770130848 76
1770130853 76
1770130858 76
1770130863 78
1770130868 78
1770130873 78
1770130878 78
1770130883 78
1770130888 78
1770130893 78
1770130898 78
```
</details>

---

