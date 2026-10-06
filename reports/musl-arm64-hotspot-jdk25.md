---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:55:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 35-42 cores)</summary>

```
1791280145 35
1791280150 35
1791280155 35
1791280160 35
1791280165 35
1791280170 37
1791280175 37
1791280180 42
1791280185 42
1791280190 41
1791280195 41
1791280200 41
1791280205 41
1791280210 41
1791280215 41
1791280220 41
1791280225 41
1791280230 36
1791280235 36
1791280240 36
```
</details>

---

