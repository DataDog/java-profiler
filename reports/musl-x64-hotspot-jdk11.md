---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:12 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 14.78/sec |
| Health Score | 924% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1790763120 85
1790763125 85
1790763130 85
1790763135 96
1790763140 96
1790763145 96
1790763150 96
1790763155 96
1790763160 96
1790763165 94
1790763170 94
1790763175 94
1790763180 94
1790763185 94
1790763190 94
1790763195 94
1790763200 94
1790763205 94
1790763210 94
1790763215 94
```
</details>

---

