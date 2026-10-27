---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:44:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 72-85 cores)</summary>

```
1793101148 85
1793101153 85
1793101158 85
1793101163 85
1793101168 85
1793101173 76
1793101178 76
1793101183 76
1793101188 76
1793101193 76
1793101198 76
1793101203 76
1793101208 76
1793101213 76
1793101218 76
1793101223 76
1793101228 76
1793101233 76
1793101238 76
1793101243 74
```
</details>

---

