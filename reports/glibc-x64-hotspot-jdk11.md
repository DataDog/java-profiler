---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 15:07:19 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 959 |
| Sample Rate | 15.98/sec |
| Health Score | 999% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1794600114 72
1794600119 72
1794600124 72
1794600129 72
1794600134 72
1794600139 72
1794600144 72
1794600149 72
1794600154 72
1794600159 72
1794600164 72
1794600169 70
1794600174 70
1794600179 70
1794600184 70
1794600189 70
1794600194 70
1794600199 72
1794600204 72
1794600209 72
```
</details>

---

