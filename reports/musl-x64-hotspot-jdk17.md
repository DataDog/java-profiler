---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 03:34:23 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1778571008 96
1778571013 96
1778571018 96
1778571023 96
1778571028 96
1778571033 96
1778571038 96
1778571043 96
1778571048 92
1778571053 92
1778571058 92
1778571063 92
1778571068 92
1778571073 92
1778571078 92
1778571083 92
1778571088 92
1778571093 92
1778571098 92
1778571103 92
```
</details>

---

