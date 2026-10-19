---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 18:19:18 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1792448071 30
1792448076 30
1792448081 30
1792448086 30
1792448091 30
1792448096 32
1792448101 32
1792448106 32
1792448111 32
1792448116 32
1792448121 32
1792448126 32
1792448131 32
1792448136 32
1792448141 32
1792448146 32
1792448151 32
1792448156 12
1792448161 12
1792448166 12
```
</details>

---

