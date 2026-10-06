---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 09:30:44 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1791293032 13
1791293037 13
1791293042 13
1791293047 13
1791293052 13
1791293057 15
1791293062 15
1791293067 15
1791293072 15
1791293077 15
1791293082 15
1791293087 15
1791293092 15
1791293097 15
1791293102 15
1791293107 15
1791293112 15
1791293117 15
1791293122 15
1791293127 15
```
</details>

---

