---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 18:13:26 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 959 |
| Sample Rate | 15.98/sec |
| Health Score | 999% |
| Threads | 10 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1777414053 80
1777414058 80
1777414063 80
1777414068 80
1777414073 80
1777414078 82
1777414083 82
1777414088 82
1777414093 82
1777414098 82
1777414103 82
1777414108 82
1777414113 82
1777414118 82
1777414124 82
1777414129 82
1777414134 82
1777414139 82
1777414144 82
1777414149 82
```
</details>

---

