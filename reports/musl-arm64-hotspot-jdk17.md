---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-11 04:46:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 10 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1786437750 64
1786437755 64
1786437760 64
1786437765 64
1786437770 64
1786437775 64
1786437780 64
1786437785 64
1786437790 64
1786437795 64
1786437800 56
1786437806 56
1786437811 56
1786437816 56
1786437821 56
1786437826 56
1786437831 56
1786437836 56
1786437841 56
1786437846 56
```
</details>

---

