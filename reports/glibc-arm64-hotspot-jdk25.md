---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 08:32:10 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 9 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 34-44 cores)</summary>

```
1791980558 39
1791980563 39
1791980568 39
1791980573 39
1791980578 39
1791980583 39
1791980588 39
1791980593 39
1791980598 34
1791980603 34
1791980608 34
1791980613 34
1791980618 34
1791980623 34
1791980628 34
1791980633 34
1791980638 34
1791980644 34
1791980649 34
1791980654 34
```
</details>

---

