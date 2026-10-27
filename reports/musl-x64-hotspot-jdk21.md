---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:44:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 59-76 cores)</summary>

```
1793101143 76
1793101148 76
1793101153 76
1793101158 76
1793101163 76
1793101168 76
1793101173 68
1793101178 68
1793101183 59
1793101188 59
1793101193 59
1793101198 59
1793101203 59
1793101208 59
1793101213 59
1793101218 59
1793101223 59
1793101228 59
1793101233 59
1793101238 59
```
</details>

---

