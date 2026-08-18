---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 09:21:55 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (6 unique values: 62-76 cores)</summary>

```
1787059039 70
1787059044 72
1787059049 72
1787059054 72
1787059059 72
1787059064 74
1787059069 74
1787059074 74
1787059079 74
1787059084 74
1787059089 76
1787059094 76
1787059099 76
1787059104 76
1787059109 76
1787059114 76
1787059119 76
1787059124 76
1787059129 64
1787059134 64
```
</details>

---

