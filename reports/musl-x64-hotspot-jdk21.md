---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:23:45 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1788139043 96
1788139048 96
1788139053 96
1788139058 87
1788139063 87
1788139068 87
1788139073 87
1788139078 87
1788139083 87
1788139088 87
1788139094 87
1788139099 87
1788139104 87
1788139109 96
1788139114 96
1788139119 96
1788139124 96
1788139129 96
1788139134 96
1788139139 96
```
</details>

---

