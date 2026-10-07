---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 10:47:22 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791384043 48
1791384048 48
1791384053 48
1791384058 48
1791384063 48
1791384068 48
1791384073 48
1791384078 48
1791384083 48
1791384088 48
1791384093 48
1791384098 43
1791384103 43
1791384108 43
1791384113 43
1791384118 43
1791384123 43
1791384128 43
1791384133 43
1791384138 43
```
</details>

---

