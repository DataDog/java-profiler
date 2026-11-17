---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-11-17 14:55:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 15 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1794945002 51
1794945007 51
1794945013 51
1794945018 51
1794945023 51
1794945028 51
1794945033 51
1794945038 51
1794945043 51
1794945048 51
1794945053 51
1794945058 51
1794945063 51
1794945068 51
1794945073 51
1794945078 51
1794945083 51
1794945088 51
1794945093 51
1794945098 51
```
</details>

---

