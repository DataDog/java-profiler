---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 53-62 cores)</summary>

```
1795706043 62
1795706048 62
1795706053 53
1795706058 53
1795706063 53
1795706068 53
1795706073 53
1795706078 53
1795706083 53
1795706088 53
1795706093 53
1795706098 53
1795706103 53
1795706108 53
1795706113 53
1795706118 53
1795706123 53
1795706128 53
1795706133 53
1795706138 53
```
</details>

---

