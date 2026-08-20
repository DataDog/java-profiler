---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 08:52:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787230132 46
1787230137 46
1787230142 46
1787230147 48
1787230152 48
1787230157 48
1787230162 48
1787230167 43
1787230172 43
1787230177 43
1787230182 43
1787230187 43
1787230192 43
1787230197 43
1787230202 43
1787230207 43
1787230212 43
1787230217 43
1787230222 48
1787230227 48
```
</details>

---

