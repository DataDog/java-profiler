---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 05:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1795085012 71
1795085017 71
1795085022 71
1795085027 71
1795085032 71
1795085037 71
1795085042 71
1795085047 69
1795085052 69
1795085057 69
1795085062 69
1795085067 69
1795085072 69
1795085077 69
1795085082 69
1795085087 69
1795085092 69
1795085097 69
1795085102 69
1795085107 69
```
</details>

---

