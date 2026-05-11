---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-11 10:05:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 70-83 cores)</summary>

```
1778508065 71
1778508070 74
1778508075 74
1778508080 74
1778508085 70
1778508090 70
1778508095 70
1778508100 70
1778508105 70
1778508110 76
1778508115 76
1778508120 83
1778508125 83
1778508130 83
1778508135 83
1778508140 83
1778508145 83
1778508150 78
1778508155 78
1778508160 78
```
</details>

---

