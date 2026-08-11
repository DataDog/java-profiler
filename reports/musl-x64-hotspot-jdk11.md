---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 10:11:28 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 78-83 cores)</summary>

```
1786457187 81
1786457192 81
1786457197 81
1786457202 81
1786457207 81
1786457212 81
1786457217 81
1786457222 81
1786457227 81
1786457232 83
1786457237 83
1786457242 83
1786457247 83
1786457252 83
1786457257 83
1786457262 83
1786457267 83
1786457272 83
1786457277 83
1786457282 83
```
</details>

---

