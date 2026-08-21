---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-21 11:01:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 69-77 cores)</summary>

```
1787324196 73
1787324201 73
1787324206 71
1787324211 71
1787324216 69
1787324221 69
1787324226 69
1787324231 71
1787324236 71
1787324241 71
1787324246 71
1787324251 73
1787324256 73
1787324261 73
1787324266 73
1787324271 77
1787324276 77
1787324281 77
1787324286 77
1787324291 77
```
</details>

---

