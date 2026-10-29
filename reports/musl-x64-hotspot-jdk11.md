---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 06:55:49 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 84 |
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
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (4 unique values: 63-84 cores)</summary>

```
1793271027 63
1793271032 63
1793271037 63
1793271042 63
1793271047 63
1793271052 63
1793271057 80
1793271062 80
1793271067 80
1793271072 80
1793271077 80
1793271082 80
1793271087 80
1793271092 80
1793271097 80
1793271102 80
1793271107 82
1793271112 82
1793271117 82
1793271122 82
```
</details>

---

