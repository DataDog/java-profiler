---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:14:49 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 40-63 cores)</summary>

```
1790097052 40
1790097057 40
1790097062 42
1790097067 42
1790097072 63
1790097077 63
1790097082 63
1790097087 63
1790097092 63
1790097097 63
1790097102 63
1790097107 63
1790097112 63
1790097117 63
1790097122 63
1790097127 63
1790097132 63
1790097137 63
1790097142 63
1790097147 55
```
</details>

---

