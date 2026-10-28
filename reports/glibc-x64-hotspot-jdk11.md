---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:46:47 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 63-68 cores)</summary>

```
1793194954 68
1793194959 66
1793194964 66
1793194969 66
1793194974 66
1793194979 66
1793194984 66
1793194989 66
1793194994 66
1793194999 66
1793195004 63
1793195009 63
1793195014 63
1793195019 63
1793195024 65
1793195029 65
1793195034 65
1793195039 65
1793195044 65
1793195049 65
```
</details>

---

