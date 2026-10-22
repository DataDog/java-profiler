---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 16:56:16 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 66-76 cores)</summary>

```
1792702065 70
1792702070 70
1792702075 70
1792702080 70
1792702085 68
1792702090 68
1792702095 68
1792702100 66
1792702105 66
1792702110 66
1792702115 66
1792702120 68
1792702125 68
1792702130 68
1792702135 68
1792702140 68
1792702145 68
1792702150 68
1792702155 68
1792702160 68
```
</details>

---

