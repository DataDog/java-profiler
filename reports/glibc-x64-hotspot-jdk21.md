---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-04 13:27:46 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (2 unique values: 50-59 cores)</summary>

```
1770229075 50
1770229080 50
1770229085 50
1770229090 50
1770229095 50
1770229100 50
1770229105 50
1770229110 59
1770229115 59
1770229120 59
1770229125 59
1770229130 59
1770229135 59
1770229140 59
1770229145 59
1770229150 59
1770229155 59
1770229160 59
1770229165 59
1770229170 59
```
</details>

---

