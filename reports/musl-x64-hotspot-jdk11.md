---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:51:02 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 49-61 cores)</summary>

```
1793742147 58
1793742152 58
1793742157 58
1793742162 58
1793742167 58
1793742172 58
1793742177 58
1793742182 61
1793742187 61
1793742192 61
1793742197 61
1793742202 61
1793742207 61
1793742212 49
1793742217 49
1793742222 49
1793742227 49
1793742232 49
1793742237 49
1793742242 51
```
</details>

---

