---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:13:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 24-36 cores)</summary>

```
1793614092 31
1793614097 31
1793614102 31
1793614107 34
1793614112 34
1793614117 36
1793614122 36
1793614127 24
1793614132 24
1793614137 24
1793614142 24
1793614147 24
1793614152 24
1793614157 24
1793614162 24
1793614167 24
1793614172 24
1793614177 24
1793614182 24
1793614187 24
```
</details>

---

