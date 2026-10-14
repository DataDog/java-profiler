---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 12:30:10 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 88-93 cores)</summary>

```
1791995104 88
1791995109 88
1791995114 88
1791995119 88
1791995124 88
1791995129 88
1791995134 88
1791995139 88
1791995144 88
1791995149 88
1791995154 88
1791995159 88
1791995164 93
1791995169 93
1791995174 93
1791995179 93
1791995184 93
1791995189 93
1791995194 93
1791995199 93
```
</details>

---

