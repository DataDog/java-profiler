---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (4 unique values: 71-76 cores)</summary>

```
1794939925 73
1794939930 73
1794939935 73
1794939940 73
1794939945 76
1794939950 76
1794939955 76
1794939960 76
1794939965 74
1794939970 74
1794939975 74
1794939980 74
1794939985 76
1794939990 76
1794939995 76
1794940000 76
1794940005 76
1794940010 74
1794940015 74
1794940020 74
```
</details>

---

