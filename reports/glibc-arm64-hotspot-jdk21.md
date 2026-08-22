---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 11:45:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1787413240 46
1787413245 46
1787413250 46
1787413255 46
1787413260 46
1787413265 46
1787413270 41
1787413275 41
1787413280 43
1787413285 43
1787413290 43
1787413295 43
1787413300 43
1787413305 43
1787413310 43
1787413315 43
1787413320 43
1787413325 43
1787413330 43
1787413335 43
```
</details>

---

