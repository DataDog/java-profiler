---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1790074944 60
1790074949 60
1790074954 60
1790074959 60
1790074964 60
1790074969 60
1790074974 60
1790074979 60
1790074984 60
1790074989 60
1790074994 60
1790074999 60
1790075004 60
1790075009 60
1790075014 60
1790075019 60
1790075024 60
1790075029 60
1790075034 60
1790075039 60
```
</details>

---

