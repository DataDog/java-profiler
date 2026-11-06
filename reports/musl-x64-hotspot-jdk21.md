---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 19:52:40 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 10-32 cores)</summary>

```
1793926086 32
1793926091 32
1793926096 32
1793926101 32
1793926106 32
1793926111 32
1793926116 10
1793926121 10
1793926126 10
1793926131 10
1793926136 10
1793926141 10
1793926146 10
1793926151 10
1793926156 10
1793926161 10
1793926166 10
1793926171 10
1793926176 10
1793926181 10
```
</details>

---

