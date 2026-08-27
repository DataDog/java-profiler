---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-27 08:58:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (4 unique values: 44-54 cores)</summary>

```
1787835099 52
1787835104 52
1787835109 54
1787835114 54
1787835119 54
1787835124 54
1787835129 54
1787835134 54
1787835139 54
1787835144 54
1787835149 46
1787835154 46
1787835159 46
1787835164 46
1787835169 46
1787835174 46
1787835179 46
1787835184 46
1787835189 46
1787835194 44
```
</details>

---

