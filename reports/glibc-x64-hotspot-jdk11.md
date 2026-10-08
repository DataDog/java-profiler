---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 12:05:50 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1791475196 80
1791475201 80
1791475206 80
1791475211 80
1791475216 80
1791475221 82
1791475226 82
1791475231 82
1791475236 82
1791475241 82
1791475246 82
1791475251 83
1791475256 83
1791475261 83
1791475266 85
1791475271 85
1791475276 85
1791475281 85
1791475286 85
1791475291 85
```
</details>

---

