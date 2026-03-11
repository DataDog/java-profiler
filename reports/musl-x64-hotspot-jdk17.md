---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 16:37:28 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 6-36 cores)</summary>

```
1773261115 6
1773261120 6
1773261125 6
1773261130 6
1773261135 6
1773261140 6
1773261145 6
1773261150 6
1773261155 6
1773261160 6
1773261165 6
1773261170 36
1773261175 36
1773261180 36
1773261185 36
1773261190 11
1773261195 11
1773261200 11
1773261205 11
1773261210 11
```
</details>

---

