---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 13:17:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (4 unique values: 73-92 cores)</summary>

```
1773249099 92
1773249104 92
1773249109 92
1773249114 92
1773249119 92
1773249124 73
1773249129 73
1773249134 73
1773249139 73
1773249144 73
1773249150 73
1773249155 73
1773249160 73
1773249165 73
1773249170 75
1773249175 75
1773249180 75
1773249185 75
1773249190 75
1773249195 75
```
</details>

---

