---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-29 12:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 64-83 cores)</summary>

```
1790699275 66
1790699280 66
1790699285 66
1790699290 66
1790699295 66
1790699300 66
1790699305 66
1790699310 66
1790699315 66
1790699320 66
1790699325 66
1790699330 66
1790699335 66
1790699340 66
1790699345 66
1790699350 64
1790699355 64
1790699360 64
1790699365 64
1790699370 64
```
</details>

---

