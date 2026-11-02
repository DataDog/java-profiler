---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:02:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793635074 48
1793635079 48
1793635084 48
1793635089 48
1793635094 48
1793635099 48
1793635104 48
1793635109 48
1793635114 48
1793635119 48
1793635124 48
1793635129 48
1793635134 48
1793635140 48
1793635145 48
1793635150 48
1793635155 48
1793635160 48
1793635165 48
1793635170 48
```
</details>

---

