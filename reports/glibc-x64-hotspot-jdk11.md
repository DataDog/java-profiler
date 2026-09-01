---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 15:03:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 68-92 cores)</summary>

```
1788289081 92
1788289086 76
1788289091 76
1788289096 76
1788289101 76
1788289106 68
1788289111 68
1788289116 68
1788289121 70
1788289126 70
1788289131 70
1788289137 70
1788289142 68
1788289147 68
1788289152 68
1788289157 68
1788289162 68
1788289167 68
1788289172 68
1788289177 68
```
</details>

---

