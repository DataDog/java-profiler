---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 14:03:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 6-8 cores)</summary>

```
1786471087 6
1786471092 6
1786471097 6
1786471102 6
1786471107 6
1786471112 6
1786471117 6
1786471122 6
1786471127 6
1786471132 8
1786471137 8
1786471142 8
1786471147 8
1786471152 8
1786471157 8
1786471162 8
1786471167 8
1786471172 8
1786471177 8
1786471182 8
```
</details>

---

