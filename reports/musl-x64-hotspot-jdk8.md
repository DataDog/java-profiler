---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-20 10:11:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 70-83 cores)</summary>

```
1792504979 83
1792504984 83
1792504989 83
1792504994 83
1792504999 78
1792505004 78
1792505009 78
1792505014 78
1792505019 76
1792505024 76
1792505029 76
1792505034 76
1792505039 76
1792505044 72
1792505049 72
1792505054 74
1792505059 74
1792505064 74
1792505069 74
1792505074 74
```
</details>

---

