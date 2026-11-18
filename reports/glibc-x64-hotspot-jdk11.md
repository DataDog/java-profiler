---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:30:41 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 86 |
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
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 85-94 cores)</summary>

```
1795011976 85
1795011981 85
1795011987 94
1795011992 94
1795011997 94
1795012002 94
1795012007 94
1795012012 94
1795012017 94
1795012022 94
1795012027 94
1795012032 94
1795012037 94
1795012042 94
1795012047 94
1795012052 94
1795012057 94
1795012062 94
1795012067 94
1795012072 94
```
</details>

---

