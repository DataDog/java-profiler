---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-07 10:19:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 63-96 cores)</summary>

```
1794064475 72
1794064480 72
1794064485 74
1794064490 74
1794064495 74
1794064500 74
1794064506 74
1794064511 74
1794064516 74
1794064521 74
1794064526 74
1794064531 74
1794064536 74
1794064541 74
1794064546 74
1794064551 74
1794064556 96
1794064561 96
1794064566 96
1794064571 96
```
</details>

---

