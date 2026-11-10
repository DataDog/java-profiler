---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:01:18 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 71-93 cores)</summary>

```
1794326109 73
1794326114 73
1794326120 73
1794326125 73
1794326130 73
1794326135 73
1794326140 73
1794326145 73
1794326150 71
1794326155 71
1794326160 71
1794326165 71
1794326170 71
1794326175 71
1794326180 71
1794326185 91
1794326190 91
1794326195 91
1794326200 91
1794326205 91
```
</details>

---

