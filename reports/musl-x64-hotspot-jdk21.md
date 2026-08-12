---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:32 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1786526151 94
1786526156 94
1786526162 94
1786526167 94
1786526172 94
1786526177 94
1786526182 94
1786526187 94
1786526192 94
1786526197 94
1786526202 94
1786526207 94
1786526212 94
1786526217 94
1786526222 96
1786526227 96
1786526232 96
1786526237 96
1786526242 96
1786526247 96
```
</details>

---

