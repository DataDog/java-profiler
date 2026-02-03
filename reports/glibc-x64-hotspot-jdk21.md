---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:18:03 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770119052 30
1770119057 30
1770119062 30
1770119067 30
1770119072 30
1770119077 30
1770119082 30
1770119087 30
1770119092 30
1770119097 32
1770119102 32
1770119107 32
1770119112 32
1770119117 32
1770119122 32
1770119127 30
1770119132 30
1770119137 30
1770119142 30
1770119147 32
```
</details>

---

