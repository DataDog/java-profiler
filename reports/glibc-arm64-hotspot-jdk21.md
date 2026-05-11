---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 18:29:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1778538104 64
1778538109 64
1778538114 64
1778538119 64
1778538124 64
1778538129 64
1778538134 64
1778538139 64
1778538144 64
1778538149 64
1778538154 64
1778538159 64
1778538164 64
1778538169 64
1778538174 44
1778538179 44
1778538184 44
1778538189 44
1778538194 44
1778538199 44
```
</details>

---

