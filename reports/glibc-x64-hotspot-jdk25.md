---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-04 07:50:52 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 14.78/sec |
| Health Score | 924% |
| Threads | 13 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1770208995 68
1770209000 68
1770209005 63
1770209010 63
1770209015 63
1770209020 63
1770209025 63
1770209030 63
1770209035 63
1770209040 63
1770209045 63
1770209050 63
1770209055 63
1770209060 63
1770209065 63
1770209070 63
1770209075 63
1770209080 65
1770209085 65
1770209090 65
```
</details>

---

