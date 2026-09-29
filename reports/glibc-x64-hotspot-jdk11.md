---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 12:33:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 78-93 cores)</summary>

```
1790699290 81
1790699295 81
1790699300 81
1790699305 81
1790699310 81
1790699315 81
1790699320 81
1790699325 81
1790699330 78
1790699335 78
1790699340 78
1790699345 78
1790699350 93
1790699355 93
1790699360 93
1790699365 93
1790699370 93
1790699375 93
1790699380 93
1790699385 93
```
</details>

---

