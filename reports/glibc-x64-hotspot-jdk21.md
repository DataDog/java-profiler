---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:19:38 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (5 unique values: 23-46 cores)</summary>

```
1795004132 46
1795004137 46
1795004142 46
1795004147 46
1795004152 46
1795004157 46
1795004162 26
1795004167 26
1795004172 26
1795004177 26
1795004182 43
1795004187 43
1795004192 43
1795004197 23
1795004202 23
1795004207 23
1795004212 23
1795004217 25
1795004222 25
1795004227 25
```
</details>

---

