---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:23:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 435 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 48-64 cores)</summary>

```
1795627038 55
1795627043 48
1795627048 48
1795627053 48
1795627058 48
1795627063 48
1795627068 48
1795627073 48
1795627078 48
1795627083 48
1795627088 53
1795627093 53
1795627098 55
1795627103 55
1795627108 64
1795627113 64
1795627118 64
1795627123 64
1795627128 64
1795627133 64
```
</details>

---

