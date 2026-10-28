---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 11:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793201067 51
1793201072 51
1793201077 51
1793201082 51
1793201087 51
1793201092 51
1793201097 51
1793201102 51
1793201107 51
1793201112 51
1793201117 51
1793201122 51
1793201127 51
1793201132 51
1793201137 51
1793201142 51
1793201147 51
1793201152 51
1793201157 51
1793201162 51
```
</details>

---

