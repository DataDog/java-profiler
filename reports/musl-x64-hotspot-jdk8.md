---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 84-94 cores)</summary>

```
1769525177 94
1769525182 94
1769525187 89
1769525192 89
1769525197 89
1769525202 84
1769525207 84
1769525212 84
1769525217 84
1769525222 84
1769525227 84
1769525232 84
1769525237 84
1769525242 84
1769525247 84
1769525252 86
1769525257 86
1769525262 86
1769525267 86
1769525272 86
```
</details>

---

