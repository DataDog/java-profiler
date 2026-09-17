---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1789655041 60
1789655046 60
1789655051 60
1789655056 60
1789655061 60
1789655066 60
1789655071 60
1789655076 60
1789655081 60
1789655086 60
1789655091 64
1789655096 64
1789655101 64
1789655106 64
1789655111 64
1789655116 64
1789655121 64
1789655126 64
1789655131 64
1789655136 64
```
</details>

---

