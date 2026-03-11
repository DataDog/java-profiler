---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 08:50:42 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 25-30 cores)</summary>

```
1773232944 30
1773232949 30
1773232954 30
1773232959 30
1773232964 30
1773232969 30
1773232974 30
1773232979 30
1773232984 28
1773232989 28
1773232994 26
1773232999 26
1773233004 26
1773233009 26
1773233014 28
1773233019 28
1773233024 28
1773233029 28
1773233034 28
1773233039 25
```
</details>

---

