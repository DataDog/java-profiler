---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:21:11 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1795195046 94
1795195051 94
1795195056 86
1795195061 86
1795195066 86
1795195071 86
1795195076 86
1795195081 86
1795195086 86
1795195091 86
1795195096 86
1795195101 86
1795195106 86
1795195111 86
1795195116 86
1795195121 86
1795195126 88
1795195131 88
1795195136 88
1795195141 88
```
</details>

---

