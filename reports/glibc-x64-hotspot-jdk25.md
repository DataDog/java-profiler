---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 12 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787413235 66
1787413240 66
1787413245 66
1787413250 66
1787413255 66
1787413260 66
1787413265 66
1787413270 66
1787413275 64
1787413280 64
1787413285 64
1787413290 64
1787413295 64
1787413300 64
1787413305 64
1787413310 64
1787413315 66
1787413320 66
1787413325 66
1787413330 66
```
</details>

---

