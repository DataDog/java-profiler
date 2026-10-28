---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 11:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 36-64 cores)</summary>

```
1793201067 64
1793201072 48
1793201077 48
1793201082 48
1793201087 48
1793201092 48
1793201097 48
1793201102 48
1793201107 48
1793201112 48
1793201117 48
1793201122 48
1793201127 48
1793201132 48
1793201137 48
1793201142 48
1793201147 48
1793201152 48
1793201157 48
1793201162 48
```
</details>

---

