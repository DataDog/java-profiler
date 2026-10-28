---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 11:29:54 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 87-93 cores)</summary>

```
1793201068 93
1793201073 93
1793201078 93
1793201083 93
1793201088 93
1793201093 93
1793201098 93
1793201103 93
1793201108 93
1793201113 93
1793201118 91
1793201123 91
1793201128 91
1793201133 87
1793201138 87
1793201143 87
1793201148 87
1793201153 87
1793201158 87
1793201163 87
```
</details>

---

