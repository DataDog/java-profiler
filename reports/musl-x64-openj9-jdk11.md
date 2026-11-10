---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:01:19 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1794326100 72
1794326105 72
1794326110 72
1794326115 72
1794326120 72
1794326125 74
1794326130 74
1794326135 74
1794326140 74
1794326145 74
1794326150 74
1794326155 74
1794326160 74
1794326165 74
1794326170 74
1794326175 74
1794326180 74
1794326185 74
1794326190 74
1794326195 74
```
</details>

---

