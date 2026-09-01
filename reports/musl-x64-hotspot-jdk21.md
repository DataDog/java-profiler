---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:03:52 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 64-74 cores)</summary>

```
1788289057 72
1788289062 72
1788289067 72
1788289072 72
1788289077 74
1788289082 74
1788289087 64
1788289092 64
1788289097 64
1788289102 64
1788289107 64
1788289112 64
1788289117 64
1788289122 64
1788289127 64
1788289132 64
1788289137 64
1788289142 64
1788289147 64
1788289152 64
```
</details>

---

