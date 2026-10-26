---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 10:05:16 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 61-69 cores)</summary>

```
1793023175 67
1793023180 67
1793023185 67
1793023190 69
1793023195 69
1793023200 69
1793023205 69
1793023210 69
1793023215 67
1793023220 67
1793023225 63
1793023230 63
1793023235 61
1793023240 61
1793023245 61
1793023250 63
1793023255 63
1793023260 65
1793023265 65
1793023270 65
```
</details>

---

