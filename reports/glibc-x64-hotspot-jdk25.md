---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 81-88 cores)</summary>

```
1794340106 83
1794340111 83
1794340116 81
1794340121 81
1794340126 81
1794340131 81
1794340136 81
1794340141 81
1794340146 81
1794340151 81
1794340156 81
1794340161 81
1794340166 88
1794340171 88
1794340176 88
1794340181 88
1794340186 88
1794340191 88
1794340197 88
1794340202 88
```
</details>

---

