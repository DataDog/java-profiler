---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 03:49:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1786607102 11
1786607107 32
1786607112 32
1786607117 32
1786607122 32
1786607127 32
1786607132 32
1786607137 32
1786607142 32
1786607147 32
1786607152 32
1786607157 32
1786607162 32
1786607167 32
1786607172 32
1786607177 32
1786607182 32
1786607187 20
1786607192 20
1786607197 20
```
</details>

---

