---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 05:42:59 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1793875110 29
1793875115 29
1793875120 32
1793875125 32
1793875130 32
1793875135 32
1793875140 32
1793875145 32
1793875150 32
1793875155 32
1793875160 32
1793875165 32
1793875170 32
1793875175 32
1793875180 32
1793875185 32
1793875190 32
1793875195 32
1793875200 32
1793875205 32
```
</details>

---

