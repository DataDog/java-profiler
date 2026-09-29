---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 16:22:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1790713105 12
1790713110 12
1790713115 32
1790713120 32
1790713125 32
1790713130 32
1790713135 32
1790713140 32
1790713145 32
1790713150 32
1790713155 32
1790713160 32
1790713165 32
1790713170 32
1790713175 32
1790713180 32
1790713185 32
1790713190 32
1790713195 32
1790713200 32
```
</details>

---

