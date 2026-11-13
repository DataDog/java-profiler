---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:24:52 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 568 |

<details>
<summary>CPU Timeline (3 unique values: 67-79 cores)</summary>

```
1794594079 67
1794594084 67
1794594089 67
1794594094 67
1794594099 67
1794594104 67
1794594109 67
1794594114 67
1794594119 67
1794594124 67
1794594129 67
1794594134 67
1794594139 67
1794594144 77
1794594149 77
1794594154 79
1794594159 79
1794594164 79
1794594169 79
1794594174 79
```
</details>

---

