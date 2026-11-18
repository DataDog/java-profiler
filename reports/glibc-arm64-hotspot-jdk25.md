---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:31:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1795012095 28
1795012100 28
1795012105 28
1795012110 28
1795012115 28
1795012120 28
1795012125 28
1795012130 28
1795012135 28
1795012140 28
1795012145 28
1795012150 28
1795012155 28
1795012160 28
1795012165 28
1795012170 28
1795012175 28
1795012180 28
1795012185 28
1795012190 28
```
</details>

---

